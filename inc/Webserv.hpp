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

typedef std::string::iterator								string_it;
typedef	std::string::const_iterator							cstring_it;
typedef std::vector<std::string>							vstring;
typedef std::vector<std::string>::iterator					vstring_it;
typedef std::vector<std::string>::const_iterator			cvstring_it;

namespace webserv
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

inline static void	displayError(const std::string& message)
{
	std::cout << RED << "[ ✘ ] " << message << std::endl;
}

inline static void	usage()
{
	std::cout << BWHT << MAIN << "\t+-------------------------------------------------------+\n" << "\t|" \
			<< webserv::BWHT << "\t\tUsage: " << MAIN << "./webserv [config file]" \
			<< "\t\t|\n" << "\t+-------------------------------------------------------+" \
			<< webserv::CRST << std::endl;
}

}

#endif