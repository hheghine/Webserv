#ifndef SERVER_HPP
# define SERVER_HPP

# include <stack>
# include "a_server.hpp"


/*-------------- SERVER CLASS --------------*/
class Server : public AServer {
	private:
		std::string			_server_name;
		std::vector<int>	_ports;

	public:
		Server();

	public:
		enum vars {
			SERVER_NAME = 115,
			LISTEN = 108,
			INDEX = 105,
			ROOT = 114,
			AUTOINDEX = 97,
			METHODS = 109
		};

	public:
		void set_server_name(const svector& line);
		void set_ports(const svector& line);
};

#endif