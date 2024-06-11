#include "webserv.hpp"
#include "parser.hpp"
#include "server_core.hpp"

using namespace wb;


int	main(int ac, char** av)
{
	if (ac != 2)
	{
		wb::usage();
		return 0;
	}

	const std::string	filename = av[1];

	ServerCore* data = new ServerCore();

	try {
		data->run(filename);

		// for (std::vector<Server *>::iterator it = data->_servers.begin(); it != data->_servers.end(); ++it)
		// {
		// 	hosts_map map = (*it)->get_hosts_map();

		// 	for (const_host_it iter = map.begin(); iter != map.end(); ++iter)
		// 	{
		// 		std::cout << "host: " << iter->first << " >>>>>>> ";
		// 		for (std::vector<u_short>::const_iterator i = iter->second.begin(); i != iter->second.end(); ++i )
		// 			std::cout << "port: " << *i << " ";
		// 		std::cout << std::endl;
		// 	}
		// }
	} catch (const std::exception& e) {
		std::cout << RED << "[ ✘ ] " << e.what() << CRST << std::endl;
	}

	delete data;
}
