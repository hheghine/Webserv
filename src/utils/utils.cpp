#include "utils.hpp"

using namespace wb;


bool utils::file_exists(const std::string& filename, int flag)
{
	return (open(filename.c_str(), flag));
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
	return (vec);
}

int utils::to_int(const std::string& line)
{
	std::stringstream	ss(line);
	int					val = 0;

	ss >> val;

	if (ss.fail() || !ss.eof())
		throw std::invalid_argument("invalid argument: '" + line + "'");

	return val;
}

unsigned int utils::to_uint(const std::string& line)
{
	std::stringstream	ss(line);
	unsigned int		val = 0;

	ss >> val;

	if (ss.fail() || !ss.eof())
		throw std::invalid_argument("invalid argument: '" + line + "'");

	return val;
}

u_short utils::extract_port(const std::string& line)
{
	std::stringstream ss(line);
	int val = 0;
	char remaining;

	if (!(ss >> val) || ss.get(remaining) || \
	val < 0 || val > 65535)
		throw std::invalid_argument("invalid port: " + line);
	return static_cast<u_short>(val);
}

std::string utils::extract_str_before(const std::string& str, char c)
{
	std::string::const_iterator it = str.begin();

	while (it != str.end() && *it != c)
		it ++;

	return std::string(str.begin(), it);
}

std::string utils::extract_str_after(const std::string& str, char c)
{
	std::string::const_iterator it = str.begin();

	while (it != str.end() && *it != c)
		it ++;

	if (it == str.end())
		return "";

	it ++;
	return std::string(it, str.end());
}

void utils::ip_check(const std::string& ip)
{
	int dot = 0;
	std::string::const_iterator start = ip.begin();
	std::string::const_iterator end = start;

	for (std::string::const_iterator it = start; it != ip.end(); ++it)
	{
		if (*it == '.')
		{
			dot++;
			end = it;
			int num = utils::to_int(std::string(start, end));
			if (num < 0 || num > 255)
				throw std::invalid_argument("invalid ip: " + ip);
			start = it + 1;
		}
	}

	if (start != ip.end())
	{
		int num = utils::to_int(std::string(start, ip.end()));
		if (num < 0 || num > 255)
			throw std::invalid_argument("invalid ip: " + ip);
	}

	if (dot != 3)
		throw std::invalid_argument("invalid ip: " + ip);
}

std::string utils::size_t_to_string(size_t value)
{
	std::ostringstream os;
	os << value;
	return os.str();
}
