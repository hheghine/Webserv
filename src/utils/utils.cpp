#include "utils.hpp"
#include <iostream>

bool utils::file_exists(const std::string& filename)
{
	return (access(filename.c_str(), F_OK) != -1);
}

bool utils::is_directory(const std::string& path)
{
	DIR* dir = opendir(path.c_str());

	if (!dir)
		return false;
	closedir(dir);
	return true;
}

svector utils::split_line(const std::string& line)
{
	std::stringstream ss(line);

	std::vector<std::string> vec;
	std::string	word;

	while (ss >> word)
		vec.push_back(word);
	return vec;
}