#ifndef SERVER_CORE_HPP
# define SERVER_CORE_HPP

# include "parser.hpp"
# include "responder.hpp"
# include <list>
# include <cstring>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>

namespace wb
{

void	cgiParse(ServerCore *server, const std::string& url);

class ServerCore
{
	public:
		ServerCore();
		ServerCore(const std::vector<Server *>& _servers);
		~ServerCore();
	public:
		void run();
	private:
		struct Listener {
			Listener() {}
			Listener(int socket) : socket(socket) {}
			int			socket;
			u_short		port;
			in_addr_t	host;
			bool		operator==(const Listener& right)
			{
				return (this->socket == right.socket);
			}
		};
	private:
		int						_num;
		std::vector<Server *>	_servers;
		Responder				_responder;
		std::vector<Listener>	_listen_sockets;
		std::list<int>			_client_sockets;
		std::list<int>			_client_fds;
		std::vector<int>		_read_fd;
		std::vector<int>		_write_fd;
	private:
		void _create_listen_sockets();
		void _create_client_sockets(const Listener& listener, std::vector<int>& vec);
		void _init_listen_socket(const std::string& ip, const std::vector<u_short>& ports, int& idx);
};

}

#endif