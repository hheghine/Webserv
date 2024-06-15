#include "responder.hpp"

using namespace wb;


Responder::Responder(std::vector<Server *> servers)
	: _servers(servers)
{
	FD_ZERO(&_master);
	FD_ZERO(&_exception_fd);
}

fd_set& Responder::get_master()
{
	return _master;
}

fd_set& Responder::get_exception_fd()
{
	return _exception_fd;
}