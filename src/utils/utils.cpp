#include "utils.hpp"


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
	return vec;
}

int utils::to_int(const std::string& line)
{
	std::stringstream ss(line);
	int val = 0;

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

// void utils::ip_check(const std::string& ip)
// {
// 	int dot = 0;
// 	std::string::const_iterator start = ip.begin();
// 	std::string::const_iterator end = start;
// 	std::string::const_iterator it = start;

// 	for (; it != ip.end(); ++it)
// 	{
// 		end = ip.end();

// 		if (*it == '.')
// 		{
// 			dot ++;
// 			end = it;
// 		}
// 		if (dot == 3 || *end == '.')
// 		{
// 			int num = utils::to_int(std::string(start, end));
// 			if (num < 0 || num > 255)
// 				throw std::invalid_argument("invalid ip: " + ip);
// 			it ++;
// 			start = it;
// 		}
// 	}

// 	if (dot != 3)
// 		throw std::invalid_argument("invalid ip: " + ip);
// }

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
            start = it + 1;  // Move start to the next character after the dot
        }
    }

    // Check the last segment after the last dot
    if (start != ip.end())
    {
        int num = utils::to_int(std::string(start, ip.end()));
        if (num < 0 || num > 255)
            throw std::invalid_argument("invalid ip: " + ip);
    }

    // Ensure exactly 3 dots were found
    if (dot != 3)
        throw std::invalid_argument("invalid ip: " + ip);
}
