#include "Webserv.hpp"

int	main(int ac, char** av)
{
	(void)av;
	if (ac != 2)
	{
		webserv::usage();
		return 0;
	}
	const std::string	filename = av[1];
}
