#include "responder.hpp"
#include <strings.h>

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

void Responder::add_to_map(const int& fd, const u_short& port, const in_addr_t& host)
{
	// _fd_host_map[fd]._fd = fd;
	_fd_host_map[fd]._port = port;
	_fd_host_map[fd]._ip = host;
	_fd_host_map[fd]._code_resp = 200;
}

bool Responder::ready_to_send(int fd)
{
	return (_fd_host_map[fd]._status == SEND || _fd_host_map[fd]._status == SENDBODY);
}

void Responder::action(int fd)
{
	int status = _fd_host_map[fd]._status;

	switch(status)
	{
		case NONE:
			start_session(fd);
			break ;
		case SEND:
			break ;
		case SENDBODY:
			break ;
	}
}

void Responder::start_session(int fd)
{
	fd_data& data = _fd_host_map[fd];
	data._fd = fd;
	data._response = "";
	bzero(_buff, BUFFER);
	data._bytes_read = recv(fd, &_buff, BUFFER, 0);

	if (data._bytes_read <= 0)
	{
		FD_CLR(fd, &_master);
		close(fd);
		std::cout << GRN << "fd [ " << fd << " ] closed !" << CRST << std::endl;
		return ;
	}
	std::cout << "\nREQUEST >>>>>>>>>>>>>>>>>>>>\n" << _buff << std::endl;

}