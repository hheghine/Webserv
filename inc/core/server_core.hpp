#ifndef SERVER_CORE_HPP
# define SERVER_CORE_HPP

# include "parser.hpp"
# include "responder.hpp"
# include <list>
# include <cstring>

namespace wb
{

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


	private:
		void _create_listen_sockets();
		void _init_listen_socket(const std::string& ip, const std::vector<u_short>& ports, int idx);


};

}

#endif