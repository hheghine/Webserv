#include "ConfigParser.h"

int ConfigParser::countLineFile = 0;

std::vector<std::string> ConfigParser::supportedMethods = getSupportedMethods();
std::vector<std::string> ConfigParser::supportedHttpVersions = getSupportedHttpVersions();

std::vector<std::string> ConfigParser::getSupportedMethods()
{
	std::vector<std::string> methods;
	methods.push_back("GET");
	methods.push_back("POST");
	methods.push_back("DELETE");
	methods.push_back("PUT");
	return (methods);
}

std::vector<std::string>	ConfigParser::getSupportedHttpVersions()
{
	std::vector<std::string> versions;
	versions.push_back("HTTP/1.0");
	versions.push_back("HTTP/1.1");
	return (versions);
}

void ConfigParser::printServers()
{
	for (size_t i = 0; i < _servers.size(); i++)
	{
		std::cout << "============ SERVER " << i + 1 << " ===========\n"
				  << std::endl;
		_servers[i].printServer();
		std::cout << std::endl;
	}
}

bool ConfigParser::isMethodSupported(std::string method)
{
	return (std::find(ConfigParser::supportedMethods.begin(), ConfigParser::supportedMethods.end(), method) != ConfigParser::supportedMethods.end());
}

bool ConfigParser::isHttpVersionSupported(std::string version)
{
	return (std::find(ConfigParser::supportedHttpVersions.begin(), ConfigParser::supportedHttpVersions.end(), version) != ConfigParser::supportedHttpVersions.end());
}

bool ConfigParser::isStartBlockServer(std::vector<std::string> tokens)
{
	return ((tokens.size() == 2 && tokens[0] == "server" && tokens[1] == "{")) 
				|| (tokens.size() == 1 && tokens[0] == "server{");
}

void ConfigParser::checkDoubleServerName()
{
	std::vector<std::string> serverNames;

	for (size_t i = 0; i < _servers.size(); i++){
		std::vector<std::string> currNames = _servers[i].getServerNames();
		for (size_t j = i + 1; j < _servers.size(); j++)
        {
			if (_servers[j].isServerNamePresent(currNames))
				Logger::log(FATAL, "conflicting server name \"%s\" on %s", currNames[0].c_str(), currNames[1].c_str());
		}
	}
}

void ConfigParser::assignConfigs()
{
	for (size_t i = 0; i < _servers.size(); i++)
    {
		std::map<std::string, ListenConfig> listens = _servers[i].getListens();
		for (std::map<std::string, ListenConfig>::iterator it = listens.begin(); it != listens.end() ; ++it)
			_configs[it->first].push_back(_servers[i]);
	}
}

void ConfigParser::parse(const std::string& filename)
{
	this->_filename = filename;
	Logger::log(DEBUG, "Parsing config file: %s", _filename.c_str());
	std::ifstream configFile(_filename.c_str());
	std::vector<std::string> tokens;
	std::string line;

	if (!configFile.is_open())
		Logger::log(FATAL, "File %s can't be opened or doesn't exist", _filename.c_str());
	while (std::getline(configFile, line))
	{
		ConfigParser::countLineFile++;
		line = Utils::trimLine(line);
		if (line.empty() || line[0] == '#')
			continue;
		tokens = Utils::split(line, " ");
		if (isStartBlockServer(tokens))
        {
			ServerBlock server(_filename);
			_servers.push_back(server.getServerConfig(configFile));
		}
		else
			Logger::log(FATAL, "Invalid line: \"%s\" in file: %s:%d", line.c_str(), _filename.c_str(), ConfigParser::countLineFile);
	}
	// add Default server if no server block
	if (_servers.size() == 0)
    {
		ServerBlock server(_filename);
		_servers.push_back(server.getServerConfig(configFile));
	}
	checkDoubleServerName();
	assignConfigs();
	configFile.close();
}