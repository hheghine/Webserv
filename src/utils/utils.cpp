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

int utils::to_int(const std::string& line)
{
	std::stringstream ss(line);
	int val = 0;
	char remaining;

	if (!(ss >> val) || ss.get(remaining) || \
	val < 0 || val > 65535)
		throw std::invalid_argument("invalid port: " + line);
	return val;
}