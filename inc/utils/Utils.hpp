#ifndef UTILS_HPP
# define UTILS_HPP

# include "Webserv.hpp"

namespace utils
{

int	toInt(const std::string& format);
int	toInt(string_it start, string_it end);
int	toInt(cstring_it start, cstring_it end);

std::string	toString(const vstring& vec, const std::string& delim = "\n");
std::string	toString(const int& num);

vstring		toVString(const std::string& str, const char& c);
std::string	ltrim(const std::string& str);

string_it	search(string_it start, string_it end, const std::string& key);
cstring_it	search(cstring_it start, cstring_it end, const std::string& key);
cstring_it	search(cstring_it start, cstring_it end, const char& c);

bool	find(cstring_it start, cstring_it end, const char& c);
bool	find(cstring_it start, cstring_it end, const std::string& str);

vstring split(const std::string& str, const char& sep = ' ');
vstring split(const std ::string& str, const std::string& sep = " ");

bool	fileExists(const std::string& filename);
bool	isDirectory(const std::string& path);

std::vector<std::string>	readLines(const std::string& filename);
std::string					readText(const std::string& filename);

};

#endif