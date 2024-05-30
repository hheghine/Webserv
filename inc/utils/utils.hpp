#ifndef UTILS_HPP
# define UTILS_HPP

/*----------- STANDARD LIBRARIES -----------*/
#include <iostream>
# include <algorithm>
# include <string>
# include <vector>
# include <sstream>
# include <dirent.h>
# include <unistd.h>
#include <fcntl.h>

/*----------------- ALIASES -----------------*/
typedef std::vector<std::string> svector;

namespace utils
{

/* checks if the file exists with specified permission */
bool		file_exists(const std::string& filename, int flag);
/* checks if the directory exists */
bool		is_directory(const std::string& path);
/* splits the string and creates a vector */
svector 	split_line(const std::string& line);
/* string to int secure converter */
int			to_int(const std::string& line);
/* extracts u_short from string */
u_short		extract_port(const std::string& line);
/* extracts string before specified character */
std::string	extract_str_before(const std::string& line, char c);
/* extracts string after specified character */
std::string	extract_str_after(const std::string& line, char c);
void		ip_check(const std::string& ip);

};

#endif