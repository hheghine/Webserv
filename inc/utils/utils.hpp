#ifndef UTILS_HPP
# define UTILS_HPP

# include <string>
# include <vector>
# include <sstream>
# include <dirent.h>
# include <unistd.h>
# include <algorithm>

typedef std::vector<std::string> svector;

namespace utils
{

enum perm
{
	EX_OK = 1,
	WR_OK = 2,
	RD_OK = 4
};

bool	file_exists(const std::string& filename, int flag);
bool	is_directory(const std::string& path);
svector split_line(const std::string& line);
int		to_int(const std::string& line);

};

#endif