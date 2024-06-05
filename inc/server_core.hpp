#ifndef SERVER_CORE_HPP
# define SERVER_CORE_HPP

# include "webserv.hpp"
# include "parser.hpp"
# include "server.hpp"
# include <list>
# include <cstring>

class ServerCore {
	public:
		ServerCore();
		~ServerCore();

		std::vector<Server *>	_servers;

	private:

	struct Listener {
		int			socket;
		u_short		port;
		in_addr_t	host;
	};

	private:
		std::vector<Listener>	_listen_sockets;
		std::list<int>			_client_sockets;
		int						_num;

	private:
		void _create_listen_sockets();
		void _init_listen_socket(in_addr_t host, const std::vector<u_short>& ports, int idx);


};

#endif