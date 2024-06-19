#ifndef RESPONDER_HPP
# define RESPONDER_HPP

# include "webserv.hpp"
# include "server.hpp"
# include <netinet/in.h>
# include <sstream>

# define BUFFER 2048

namespace wb
{

enum session_status
{ NONE, SEND, SENDBODY };

struct fd_data
{
	in_addr_t	_ip;
	u_short		_port;
		int		_fd;
		int		_status;
		int		_code_resp;
	std::string	_request_type;
	std::string	_protocol; // http1.1
	std::string _response;
	ssize_t		_bytes_read;
		int		_body_len;
	std::string _file_path;
};

class Responder {
	public:
		Responder(std::vector<Server *> servers);

	private:
		std::vector<Server *>&	_servers;
			fd_set				_master;
			fd_set				_exception_fd;
		std::map<int, fd_data>	_fd_host_map;

	public:
			char				_buff[BUFFER]; // later gonna be private, no getter is needed
		fd_set&	get_master();
		fd_set&	get_exception_fd();

		void	add_to_map(const int& fd, const u_short& port, const in_addr_t& host);
		bool	ready_to_send(int fd);
		void	action(int fd);
		void	start_session(int fd);
		void	parse_html_request(fd_data& data, const std::string& buffer);
};

}

#endif