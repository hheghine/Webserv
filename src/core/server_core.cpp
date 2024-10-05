#include "server_core.hpp"
#include <sys/time.h>

using namespace wb;


ServerCore::ServerCore()
	: _num(0)
	// , _responder(_servers)
{}

ServerCore::ServerCore(const std::vector<Server *>& _servers)
	: _num(0)
	, _servers(_servers)
	, _responder(Responder(_servers))
{}

/***********************TEMPORARY***********************/

/**********************************************************/

void ServerCore::run()
{
	// std::cout << "this is : " << p._servers.size() << std::endl;
	// this->_responder = Responder();
	// this->_responder._servers = std::vector<Server *>();
	// printf("%s\n", this->_servers[0]->_index.c_str());
	
	struct timeval	timeout;

	timeout.tv_sec = 10;
	_create_listen_sockets();
	for (size_t i = 0; i < this->_listen_sockets.size(); ++i)
		std::cout << this->_listen_sockets[i].socket << std::endl;
	// std::string html_content = read_html_file("www/index.html");
	while (1) //_num
	{
		// try
		// {	
			fd_set read_fd = _responder.get_read_master();
			fd_set write_fd = _responder.get_write_master();
			int res = select(this->_num, &read_fd, &write_fd, 0, 0);
			if (res <= 0)
			{
				// perror("lave: ");
				std::cout << "select failed with: " << res << std::endl;;
				continue ;
			}
			for (int sock = 3; sock < this->_num; ++sock)
			{
				cgiParse(this, "www/cgi-bin/cgi.py?a=b&c=d");
				printf ("bbbb\n");
				std::vector<Listener>::iterator elem = std::find(_listen_sockets.begin(), _listen_sockets.end(), Listener(sock));
				if (FD_ISSET(sock, &read_fd) && elem != _listen_sockets.end())
				{
					_create_client_sockets(*elem, _read_fd);
					FD_SET(sock, &_responder.get_read_master());
				}
				if (FD_ISSET(sock, &read_fd) && !_responder.ready_to_send(sock))
				{
					std::string	response;
					_responder.action(response, sock);
				}
			}
			
		// }
		// catch(const std::exception& e)
		// {
		// 	std::cerr << e.what() << '\n';
		// }

		


/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
		// std::cout << "this are : " << this->_responder._servers.size() << std::endl;
		// if ( select(_num, &read_fd, &write_fd, 0, 0) <= 0 )
		// 	continue ;
		
		// for(size_t i = 0; i < _listen_sockets.size(); ++i)
		// {
		// 	if (FD_ISSET(_listen_sockets[i].socket, &read_fd))
		// 	{
		// 		_create_client_sockets(_listen_sockets[i], _read_fd);
		// 	}
		// }

		// for (std::list<int>::iterator it = _client_sockets.begin(); \
		// 		it != _client_sockets.end(); ++it)
		// {
		// 	/***************************TEMPORARY***************************/
			
			
		// 	std::cout << "gde  : " <<  this->_responder._servers.size() << std::endl;
			
		// 	std::string response;
		// 	// response = "HTTP/1.1 200 OK\r\nContent-Type: ''\r\nContent-Length: " +
		// 	// utils::size_t_to_string(html_content.size()) + "\r\n\r\n" + html_content;

		// 	// std::cout << html_content.size() << "-----------------------\n";
		// 	// std::string response;
		// 	// if ()
		// 	if (FD_ISSET(*it, &read_fd) && !_responder.ready_to_send(*it))
		// 	{
		// 		_responder.action(response, *it);
		// 	}

		// 	if (FD_ISSET(*it, &write_fd) && _responder.ready_to_send(*it))
		// 	{
		// 		_responder.action(response, *it);
		// 	}

		// 	std::string sendresp = std::string("HTTP/1.1 200 OK\r\nContent-Type: ''\r\nContent-Length: " + utils::size_t_to_string(response.size())) + std::string("\r\n\r\n") + response;
		// 	response = sendresp;
		// 	// parseRequest();

		// 	// if ()

		// 	// cgiParse(this, "/cgi/bin/cgi.py?a=b&b=c");

		// 	// response = 
		// 	std::cout << "i want to send yoyuuuu: '" << response.c_str() << "'" << std::endl;
		// 	send(*it, response.c_str(), response.size(), 0);
			// int ret = recv(*it, _responder._buff, BUFFER, MSG_DONTWAIT);
			// if (ret < 0)
			// 	continue ;

			// ret = send(*it, _responder._buff, BUFFER, MSG_DONTWAIT);
			// if (ret < 0)
			// 	continue ;
		// }
/////////////////////////////////////////////////////////////		

		
/////////////////////////////////////////////////////////////
		// {

		// 	/***************************TEMPORARY***************************/
		// 	std::string response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: " +
		// 	utils::size_t_to_string(html_content.size()) + "\r\n\r\n" + html_content;

		// 	int ret = recv(*it, _responder._buff, BUFFER, MSG_DONTWAIT);
		// 	std::cout << "\n\nshya budet info\n" << std::endl;
		// 	std::cout <<  _responder._buff << std::endl;
		// 	close(*it);
		// 	FD_CLR(*it, &_responder.get_master());
		// 	it = _client_sockets.erase(it);
		// 	if (it == _client_sockets.end())
		// 		break;
		// 	/****************************************************************/

		// 	send(*it, response.c_str(), response.size(), 0);

		// 	if (FD_ISSET(*it, &read_fd) && !_responder.ready_to_send(*it))
		// 	{
		// 		_responder.action(*it);
		// 	}

		// 	if (FD_ISSET(*it, &write_fd) && _responder.ready_to_send(*it))
		// 	{
		// 		_responder.action(*it);
		// 	}
		// 	// send(*it, _responder._buff, BUFFER, MSG_DONTWAIT);
		// 	// int ret = recv(*it, _responder._buff, BUFFER, MSG_DONTWAIT);
		// 	// if (ret < 0)
		// 	// 	continue ;

		// 	// if (ret < 0)
		// 	// 	continue ;
		// }
	}
}

ServerCore::~ServerCore()
{
	for (std::vector<Server *>::iterator it = _servers.begin(); it != _servers.end(); ++ it)
		delete *it;
}

in_addr_t	convertToInetAddr(std::string host)
{
	in_addr_t	ret = 0;
	in_addr_t	part = 0;
	size_t		pos = 0;

	for (size_t i = 0; i < 3; ++i)
	{
		pos = host.find_first_of('.');
		if (pos == host.npos)
			throw std::invalid_argument("Invalid IP address!");
		part = utils::to_uint(host.substr(0, pos));
		for (size_t j = 0; j < i; ++j)
			part *= 256;
		host = host.substr(pos + 1);
		ret += part;
	}
	part = utils::to_uint(host);
	ret += (part * 256 * 256 * 256);
	return (ret);
}

void ServerCore::_create_listen_sockets()
{
	int idx = -1;
	_listen_sockets.reserve(3);
	
	for (size_t i = 0; i < _servers.size(); ++i)
	{
		hosts_map map = _servers[i]->get_hosts_map();
		for (const_host_it it = map.begin(); it != map.end(); ++it)
			_init_listen_socket(it->first, map[it->first], idx);
	}
}

void ServerCore::_init_listen_socket(\
				const std::string& ip, \
				const std::vector<u_short>& ports, \
				int& idx)
{
	std::cout << "ports size: " << ports.size() << std::endl;
	for (std::vector<u_short>::const_iterator it = ports.begin(); it != ports.end(); ++it)
	{
		std::cout << *it << std::endl;
		_listen_sockets.push_back(Listener());
		idx ++;

		struct addrinfo		hints;
		struct addrinfo		*real;

		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_flags = 0;
		hints.ai_protocol = 0;

		if (getaddrinfo(ip.c_str(), utils::size_t_to_string(*it).c_str(), &hints, &real))
			throw std::runtime_error("error: getaddrinfo");

		_listen_sockets[idx].socket = socket(AF_INET, SOCK_STREAM, 0);
		fcntl(_listen_sockets[idx].socket, F_SETFL, O_NONBLOCK);
		struct addrinfo *element;
		for (element = real; element != NULL; element = element->ai_next)
		{
			// std::cout << utils::size_t_to_string(*it).c_str() << std::endl;
			std::cout << "binding on ip " << ip << " and port " << *it << std::endl;
			int success = !bind(_listen_sockets[idx].socket, \
								element->ai_addr, element->ai_addrlen);
			if (success)
				break ;
		}
		if (element == NULL)
		{
			perror("a:");
			throw std::runtime_error("error: bind at address " + ip + \
			" on port" + utils::size_t_to_string(*it));
		}

		int opt = 1;
		setsockopt(_listen_sockets[idx].socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

		display_time();
		std::cout << MAIN << "\t[ WEBSERV  ]" << CRST << " listen socket [ "  << MAIN \
		<< _listen_sockets[idx].socket << CRST << " ] port: " << MAIN << *it \
		<< CRST << " " /* << addressIn.sin_port*/ << " host: " << MAIN << ip << CRST \
		<< " " << std::endl;

		if (listen(_listen_sockets[idx].socket, 32))
			throw std::runtime_error("error: listen");

		FD_SET(_listen_sockets[idx].socket, &_responder.get_read_master());

		if (_listen_sockets[idx].socket >= _num)
			_num = _listen_sockets[idx].socket + 1;
	}
}

void ServerCore::_create_client_sockets(const Listener& listener, std::vector<int>& vec)
{
	// struct sockaddr_in& addressIn = reinterpret_cast<struct sockaddr_in&>(address);

	// memset(reinterpret_cast<char *>(&address), 0, sizeof(struct sockaddr));

	// addressIn.sin_family = AF_INET;
	// addressIn.sin_port = listener.port;
	// addressIn.sin_addr.s_addr = listener.host;

	struct sockaddr	address;
	socklen_t		brat = sizeof(address);
	int				fd = accept(listener.socket, &address, &brat);

	if (fd < 0)
		return ;
	vec.push_back(fd);

	fcntl(fd, F_SETFL, O_NONBLOCK);
    FD_SET(fd, &_responder.get_read_master());
	// _responder.add_to_map(fd, addressIn.sin_port, addressIn.sin_addr.s_addr);
	_client_sockets.push_back(fd);

	if (fd >= _num)
		_num = fd + 1;
}