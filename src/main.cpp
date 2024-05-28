#include "webserv.hpp"
#include "parser.hpp"
#include "data.hpp"

int	main(int ac, char** av)
{
	(void)av;
	if (ac != 2)
	{
		wb::usage();
		return 0;
	}
	const std::string	filename = av[1];

	Data* data = new Data();

	try {
		Parser p;
		p(filename, data->_servers);
	} catch (const std::exception& e) {
		std::cout << RED << "[ ✘ ] " << e.what() << std::endl;
	}

	delete data;
}
