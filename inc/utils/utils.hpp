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

bool	file_exists(const std::string& filename, int flag);
bool	is_directory(const std::string& path);
svector split_line(const std::string& line);
int		to_int(const std::string& line);

};

#endif