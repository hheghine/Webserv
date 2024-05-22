#include "webserv.hpp"
#include "parser.hpp"

int	main(int ac, char** av)
{
	(void)av;
	if (ac != 2)
	{
		wb::usage();
		return 0;
	}
	const std::string	filename = av[1];

	try {
		Parser p(filename);
	} catch (const std::exception& e) {
		std::cout << RED << "[ ✘ ] " << e.what() << std::endl;
	}
}
