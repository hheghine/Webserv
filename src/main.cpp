#include "webserv.hpp"
#include "parser.hpp"
#include "server_core.hpp"

using namespace wb;


int	main(int ac, char** av)
{
	if (ac > 2)
	{
		wb::usage();
		return 0;
	}

	std::string	filename;

	ac == 1 \
	? filename = "config/default.conf" \
	: filename = av[1];

	ServerCore* data = new ServerCore();

	try
	{
		data->run(filename);
	}
	catch (const std::exception& e)
	{
		display_time();
		std::cout << RED << "\t[    ✘     ] " \
		<< e.what() << CRST << std::endl;
	}

	delete data;
}
