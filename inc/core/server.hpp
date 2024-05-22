#ifndef SERVER_HPP
# define SERVER_HPP

# include <stack>
# include "a_server.hpp"

class Server : public AServer {
	public:
		Server();

	public:
		enum vars {
			INDEX = 105,
			ROOT = 114,
			METHODS = 109
		};
};

#endif