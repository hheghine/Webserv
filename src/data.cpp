#include "data.hpp"

Data::~Data()
{
	for (std::vector<Server *>::iterator it = _servers.begin(); it != _servers.end(); ++ it)
		delete *it;
}