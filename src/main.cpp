#include "parser.hpp"
#include "webserv.hpp"
#include "server_core.hpp"
#include <errno.h>

using namespace wb;


int	main(int ac, char** av)
{
	if (ac > 2)
	{
		wb::usage();
		return 0;
	}

	std::string	filename;

	ac < 2 \
	? filename = "config/default.conf" \
	: filename = av[1];
	
	ServerCore*	data;
	
	try
	{
		Parser p(filename);

		data = new ServerCore(p._servers);

		data->run();
		delete data;
	}
	catch (const std::exception& e)
	{
		display_time();
		std::cout << "\n" << errno << std::endl;
		std::cout << RED << "\t[    ✘     ] " \
		<< e.what() << CRST << std::endl;
		delete data;
	}

}
