#include "server_core.hpp"

ServerCore::ServerCore() : _num(0)
{
	_create_listen_sockets();
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
			in_addr_t host = inet_addr((it->first).c_str());
			_init_listen_socket(host, map[it->first], idx);
			idx ++;
		}
	}
}

void ServerCore::_init_listen_socket(in_addr_t host, const std::vector<u_short>& ports, int idx)
{
	for (std::vector<u_short>::const_iterator it = ports.begin(); it != ports.end(); ++it)
	{
		struct sockaddr address;
		struct sockaddr_in& addressIn = reinterpret_cast<struct sockaddr_in&>(address);

		memset(reinterpret_cast<char *>(&address), 0, sizeof(struct sockaddr));

		addressIn.sin_family = AF_INET;
		addressIn.sin_port = *it;
		addressIn.sin_addr.s_addr = host;

		_listen_sockets[idx].port = addressIn.sin_port;
		_listen_sockets[idx].host = addressIn.sin_addr.s_addr;
		_listen_sockets[idx].socket = socket(AF_INET, SOCK_STREAM, 0);

		std::cout << "listen socket " << _listen_sockets[idx].socket << " addr " << addressIn.sin_port << " " << addressIn.sin_addr.s_addr << std::endl;

		int opt = 1;
		setsockopt(_listen_sockets[idx].socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

		if (bind(_listen_sockets[idx].socket, &address, sizeof(address)))
			throw std::runtime_error("error: bind");

		if (listen(_listen_sockets[idx].socket, 32))
			throw std::runtime_error("error: listen");

		// FD_SET();

		if (_listen_sockets[idx].socket > _num)
			_num = _listen_sockets[idx].socket;
	}
}
