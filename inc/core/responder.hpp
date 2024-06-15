#ifndef RESPONDER_HPP
# define RESPONDER_HPP

# include "webserv.hpp"
# include "server.hpp"
# include <netinet/in.h>

# define BUFFER 2048

namespace wb
{

struct fd_data
{
	in_addr_t	_ip;
	u_short		_port;
	int			_fd;
	int			_status;
	int			_code_resp;
	// ...
};

class Responder {
	public:
		Responder(std::vector<Server *> servers);

	private:
		std::vector<Server *>&	_servers;
			fd_set				_master;
			fd_set				_exception_fd;
		std::map<int, fd_data>	_host_fd_map;

	public:
			char*				_buff[BUFFER];
		fd_set&	get_master();
		fd_set& get_exception_fd();
};

}

#endif