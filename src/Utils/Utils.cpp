#include "Utils.h"

std::string Utils::trimLine(std::string &line)
{
	const std::string white_chars = " \t\n\r\f\v";
	std::string result;

	int start = 0;
	while (white_chars.find(line[start]) != std::string::npos)
		start++;
	int end = line.size() - 1;
	while (end >= 0 && white_chars.find(line[end]) != std::string::npos)
		end--;

	for (int i = start; i <= end; i++)
		result.push_back(line[i]);

	return (result);
}

std::vector<std::string> Utils::split(std::string s, std::string delimiter)
{
	size_t pos = 0;
	std::string token;
	std::vector<std::string> result;
	s = trimLine(s);
	while ((pos = s.find(delimiter)) != std::string::npos)
	{
		token = s.substr(0, pos);
		result.push_back(token);
		s.erase(0, pos + delimiter.length());
		s = trimLine(s);
	}
	result.push_back(s);
	return (result);
}

std::string Utils::unsignedIntToString(unsigned int value)
{
	std::ostringstream oss;
	oss << value;
	return oss.str();
}

unsigned long long Utils::strToUll(std::string clientMaxBodySize)
{
	unsigned long long size = 0;
	
	std::stringstream ss(clientMaxBodySize);
	ss >> size;

	if (ss.fail() || !ss.eof())
	{
		return (0);
	}
	return (size);
}

std::string Utils::ullToStr(unsigned long long ull)
{
	std::ostringstream oss;
	oss << ull;
	return (oss.str());
}

std::string Utils::intToString(int value)
{
	std::ostringstream oss;
	oss << value;
	return oss.str();
}

int Utils::protectedCall(int ret, std::string msg, bool isFatal)
{
	if (ret < 0)
	{
		if (isFatal)
			Logger::log(FATAL, msg.c_str());
		else
			Logger::log(ERROR, msg.c_str());
	}
	return ret;
}