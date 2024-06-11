#ifndef SERVER_HPP
# define SERVER_HPP

# include <stack>
# include <netinet/in.h>
# include <arpa/inet.h>
# include "a_server.hpp"

namespace wb
{

typedef std::map<std::string, std::vector<u_short> > hosts_map;
typedef std::map<std::string, std::vector<u_short> >::iterator hosts_it;
typedef std::map<std::string, std::vector<u_short> >::const_iterator const_host_it;

/*-------------- SERVER CLASS --------------*/
class Server : public AServer {
	public:
		std::string				_server_name;
		hosts_map				_hosts;
		std::vector<u_short>	_ports; // max value 65535 same as for ports
		std::vector<u_short>	_universal_ports;
		int						_max_body_size;

	public:
		Server();

	public:
		enum vars {
			SERVER_NAME = 115,
			LISTEN = 108,
			INDEX = 105,
			ROOT = 114,
			AUTOINDEX = 97,
			METHODS = 109
		};

	public:
		void set_server_name(const svector& line);
		void set_hosts(const svector& line);
		const hosts_map& get_hosts_map() const;

	private:
		std::string extract_ip(const std::string& host);
		void		add_universal_ports(const std::string& ip);

};

}

#endif