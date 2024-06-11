#include "server_core.hpp"

using namespace wb;


ServerCore::ServerCore()
	: _num(0)
	, _responder(_servers)
{}

void ServerCore::run(const std::string& filename)
{
	Parser p(filename, this->_servers);

	_create_listen_sockets();

	// fd_set read_fd;
	// fd_set write_fd;
}

ServerCore::~ServerCore()
{
	for (std::vector<Server *>::iterator it = _servers.begin(); it != _servers.end(); ++ it)
		delete *it;
}

void ServerCore::_create_listen_sockets()
{
	for (int i = 0; i < (int)_servers.size(); ++i)
	{
		hosts_map map = _servers[i]->get_hosts_map();

		int idx = 0;
		for (const_host_it it = map.begin(); it != map.end(); ++it)
		{
			_listen_sockets.push_back(Listener());
			// in_addr_t host = inet_addr((it->first).c_str());
			_init_listen_socket(it->first, map[it->first], idx);
			idx ++;
		}
	}
}

void ServerCore::_init_listen_socket(const std::string& ip, const std::vector<u_short>& ports, int idx)
{
	in_addr_t host = inet_addr(ip.c_str());

	for (std::vector<u_short>::const_iterator it = ports.begin(); it != ports.end(); ++it)
	{
		struct sockaddr address;
		struct sockaddr_in& addressIn = reinterpret_cast<struct sockaddr_in&>(address);

		memset(reinterpret_cast<char *>(&address), 0, sizeof(struct sockaddr));

		addressIn.sin_family = AF_INET;
		addressIn.sin_port = htons(*it);
		addressIn.sin_addr.s_addr = host;

		_listen_sockets[idx].port = addressIn.sin_port;
		_listen_sockets[idx].host = addressIn.sin_addr.s_addr;
		_listen_sockets[idx].socket = socket(AF_INET, SOCK_STREAM, 0);

		display_time();
		std::cout << MAIN << "\t[ WEBSERV  ]" << CRST << " listen socket [ "  << MAIN \
		<< _listen_sockets[idx].socket << CRST << " ] port: " << MAIN << *it \
		<< CRST << " " << addressIn.sin_port << " host: " << ip << " " << addressIn.sin_addr.s_addr << std::endl;

		int opt = 1;
		setsockopt(_listen_sockets[idx].socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

		if (bind(_listen_sockets[idx].socket, &address, sizeof(address)) < 0)
			throw std::runtime_error("error: bind");

		if (listen(_listen_sockets[idx].socket, 32))
			throw std::runtime_error("error: listen");

		FD_SET(_listen_sockets[idx].socket, &_responder.get_master());

		if (_listen_sockets[idx].socket > _num)
			_num = _listen_sockets[idx].socket;
	}
}
