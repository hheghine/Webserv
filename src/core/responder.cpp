#include "responder.hpp"

using namespace wb;


Responder::Responder(std::vector<Server *> servers)
	: _servers(servers)
{
	FD_ZERO(&_master);
	FD_ZERO(&_write_master);
}

fd_set& Responder::get_master()
{
	return _master;
}