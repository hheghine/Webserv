#ifndef DATA_HPP
# define DATA_HPP

# include "server.hpp"

class Data {
	public:
		~Data();

		std::vector<Server *> _servers;
};

#endif