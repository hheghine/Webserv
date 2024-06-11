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
			fd_set				_write_master;
		std::map<int, fd_data>	_host_fd_map;
			char*				_buff[BUFFER];

	public:
		fd_set&	get_master();
		
};

}

#endif