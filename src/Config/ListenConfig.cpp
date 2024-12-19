#include "ListenConfig.h"

ListenConfig::ListenConfig() {}

ListenConfig::ListenConfig(std::string token)
{
    std::vector<std::string> ip = Utils::split(token, ":");

	if (ip.size() == 1){
		if (ip[0].find(".") != std::string::npos){
			_ip = ip[0];
			_port = 80;
		}else{
			_ip = "0.0.0.0";
			_port = std::atoi(ip[0].c_str());
		}
	}else if (ip.size() == 2){
		if (ip[0].empty() || ip[1].empty())
			Logger::log(FATAL, "Invalid Ip value: %s", token.c_str());
		_ip = ip[0];
		_port = std::atoi(ip[1].c_str());
	}else{
		Logger::log(FATAL, "Invalid listen value: %s", token.c_str());
	}
	_ip_port = _ip + ":" + Utils::unsignedIntToString(_port);
	if (!checkIpPort())
		Logger::log(FATAL, "Invalid Ip/Port value: %s", token.c_str());
}

ListenConfig::~ListenConfig() {}

/*
/ ---------------------------- CHECKERS ------------------------------- //
*/
bool ListenConfig::checkIpPort()
{
	int	i = 0;
	int	j = 0;
	std::string str = _ip_port;

	for (int p = 0; p < 3; p++)
	{
		while (isdigit(str[i + j]))
			i++;
		if (isNotInRangeIp(str, j, i))
			return (false);
		if (i == 0 || i > 3 || str[j + i++] != '.')
			return (false);
		j += i;
		i = 0;
	}
	while (isdigit(str[i + j]))
		i++;
	if (isNotInRangeIp(str, j, i))
		return (false);
	if (i == 0 || i > 3 || str[j + i++] != ':')
		return (false);
	if (_port > 65535)
		return (false);
	return (true);
}

bool ListenConfig::isNotInRangeIp(std::string str, int start, int i)
{
	std::string ip = str.substr(start, i);
	return (ip < "0" || ip > "255");
}