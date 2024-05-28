#ifndef DATA_HPP
# define DATA_HPP

# include "server.hpp"

class Data {
	public:
		~Data()
		{
			for (std::vector<Server *>::iterator it = _servers.begin(); it != _servers.end(); ++ it)
			delete *it;
		}

		std::vector<Server *> _servers;
};

#endif