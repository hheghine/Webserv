#ifndef WEBSERV_HPP
# define WEBSERV_HPP

/*-----------STANDARD LIBRARIES-----------*/
# include <iostream>
# include <fstream>
# include <vector>
# include <string>
# include <map>
# include <sstream>
# include <fcntl.h>
# include <unistd.h>
# include <signal.h>
# include <dirent.h>
# include <sys/epoll.h>
# include <sys/socket.h>

/*--------------HEADER FILES--------------*/
# include "utils.hpp"


namespace wb
{

/*------------COLOR CONSTANTS------------*/
const char* const WHT = "\033[0;37m";
const char* const GRN = "\033[0;32m";
const char* const CYN = "\033[0;36m";
const char* const GRY = "\033[0;90m";
const char* const RED = "\033[0;31m";

const char* const BWHT = "\033[1;37m";
const char* const BGRN = "\033[1;32m";
const char* const BCYN = "\033[1;36m";
const char* const BGRY = "\033[1;90m";

const char* const MAIN = "\033[38;2;153;255;102m";

const char* const CRST = "\033[0m";

/*-----------------ALIASES-----------------*/
typedef std::string::iterator								string_it;
typedef	std::string::const_iterator							string_const_it;
typedef std::vector<std::string>							svector;
typedef std::vector<std::string>::iterator					svector_it;
typedef std::vector<std::string>::const_iterator			svector_const_it;

inline static void	usage()
{
	std::cout << BWHT << MAIN << "\t+-------------------------------------------------------+\n" << "\t|" \
			<< BWHT << "\t\tUsage: " << MAIN << "./webserv [config file]" \
			<< "\t\t|\n" << "\t+-------------------------------------------------------+" \
			<< CRST << std::endl;
}

}

#endif