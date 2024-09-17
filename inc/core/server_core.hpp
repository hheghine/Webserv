#ifndef SERVER_CORE_HPP
# define SERVER_CORE_HPP

# include "parser.hpp"
# include "responder.hpp"
# include <list>
# include <cstring>

namespace wb
{

void	cgiParse(ServerCore *server, const std::string& url);

class ServerCore {
	public:
		ServerCore();
		~ServerCore();

	public:
		void run(const std::string& filename);

	private:

	struct Listener {
		int			socket;
		u_short		port;
		in_addr_t	host;
	};

	private:
		std::vector<Server *>	_servers;
		std::vector<Listener>	_listen_sockets;
		std::list<int>			_client_sockets;
		int					_num;
		Responder				_responder;
		std::vector<int>		_read_fd;
		std::vector<int>		_write_fd;


	private:
		void _create_listen_sockets();
		void _create_client_sockets(const Listener& listener, std::vector<int>& vec);
		void _init_listen_socket(const std::string& ip, const std::vector<u_short>& ports, int& idx);


};

}

#endif