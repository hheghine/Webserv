#include "ServerBlock.h"

ServerBlock::ServerBlock()
    : _clientMaxBodySize(BS_DEFAULT_CLIENT_MAX_BODY_SIZE)
    , _filename("")
{
    _counterView["root"] = 0;
    _counterView["clientMaxBodySize"] = 0;
}

ServerBlock::ServerBlock(std::string filename)
    : _clientMaxBodySize(BS_DEFAULT_CLIENT_MAX_BODY_SIZE)
    , _filename(filename)
{
    _counterView["root"] = 0;
    _counterView["clientMaxBodySize"] = 0;
}

ServerBlock::ServerBlock(const ServerBlock& rhs)
{
    *this = rhs;
}

ServerBlock& ServerBlock::operator=(const ServerBlock& rhs)
{
    if (this != &rhs)
	{
		_listen = rhs._listen;
		_serverNames = rhs._serverNames;
		_index = rhs._index;
		_root = rhs._root;
		_clientMaxBodySize = rhs._clientMaxBodySize;
		_locations = rhs._locations;
		_errorPages = rhs._errorPages;
		_filename = rhs._filename;
		_counterView = rhs._counterView;
	}
	return *this;
}

void ServerBlock::setClientMaxBodySize(std::string clientMaxBodySize)
{
	_clientMaxBodySize = Utils::strToUll(clientMaxBodySize);
	_counterView["clientMaxBodySize"]++;
}

void ServerBlock::setDefaultValue()
{
	if (_listen.empty()){
		ListenConfig listen("0.0.0.0:1234");
		_listen["0.0.0.0:1234"] = listen;
	}
	if (_root.empty())
		_root = "./www/main";
	if (_index.empty())
		_index.push_back("index.html");
}

bool ServerBlock::isServerNamePresent(std::vector<std::string>& otherNames)
{

	for (size_t i = 0; i < otherNames.size(); i++)
	{
		for (size_t j = 0; j < _serverNames.size(); j++)
		{
			if (otherNames[i] == _serverNames[j]){
				otherNames.clear();
				otherNames.push_back(_serverNames[j]);
				otherNames.push_back(_listen.begin()->first);
				return (true);
			}
		}
	}
	return (false);
}

void ServerBlock::addErrorPages(int errorCode, std::string file)
{ 
	if (errorCode < 400 || errorCode > 599)
		Logger::log(FATAL, "Invalid error code: %d in file %s:%d", errorCode, _filename.c_str()); // maybe add file line
	_errorPages[errorCode] = file; 
}

void ServerBlock::addListen(std::string &token)
{
	ListenConfig listen(token);
	
	if (_listen.find(listen.getIpPort()) != _listen.end())
		Logger::log(FATAL, "Duplicate listen in server context: %s", token.c_str());

	_listen[listen.getIpPort()] = listen;
}

void ServerBlock::addServerName(std::vector<std::string>& token)
{
	for (size_t i = 1; i < token.size(); i++)
    {
		if (std::find(_serverNames.begin(), _serverNames.end(), token[i]) == _serverNames.end())
			_serverNames.push_back(token[i]);
	}
}

void ServerBlock::addIndexes(std::vector<std::string>& token)
{
	for (size_t i = 1; i < token.size(); i++)
    {
		if (std::find(_index.begin(), _index.end(), token[i]) == _index.end())
			_index.push_back(token[i]);
	}
}

void ServerBlock::printPair(const std::string& label, const std::string& value)
{
    std::cout << std::left << label << ": " << (value.empty() ? "none" : value) << std::endl;
}

void ServerBlock::printInt(const std::string& label, int value)
{
    std::cout << std::left << label << ": " << (value == -1 ? "none" : Utils::intToString(value)) << std::endl;
}

void ServerBlock::printVector(const std::string& label, const std::vector<std::string>& vec)
{
    std::cout << std::left << label << ": " << (vec.empty() ? "none" : "") << std::endl;
    for (std::vector<std::string>::const_iterator it = vec.begin(); it != vec.end(); ++it)
        std::cout << "\t- " << *it << std::endl;
}

void ServerBlock::printMap(const std::string& label, const std::map<int, std::string>& map)
{
    std::cout << std::left << label << ": " << (map.empty() ? "none" : "") << std::endl;
    for (std::map<int, std::string>::const_iterator it = map.begin(); it != map.end(); ++it)
        std::cout << "\t- " << it->first << ": " << it->second << std::endl;
}

void ServerBlock::printListens()
{
    std::cout << std::left << "Listens" << ": " << (_listen.empty() ? "none" : "") << std::endl;
    for (std::map<std::string, ListenConfig>::const_iterator it = _listen.begin(); it != _listen.end(); ++it)
        std::cout << "\t- " << it->second.getIp() << ":" << it->second.getPort() << std::endl;
}

void ServerBlock::printServer()
{
    printVector("Server names", _serverNames);
    printListens();
    printVector("Index", _index);
    printPair("Root", _root);
	std::cout << "Client max body size: " << Utils::ullToStr(_clientMaxBodySize) << std::endl;
    printMap("Error pages", _errorPages);

    if (_locations.empty())
	{
        std::cout << std::setw(25) << std::left << "Locations" << ": none" << std::endl;
    }
    else
    {
        int i = 0;
        for (std::vector<Location>::iterator it = _locations.begin(); it != _locations.end(); ++it)
		{
            std::cout << "\n-- LOCATION " << ++i << " --" << std::endl;
            it->printLocation();
        }
    }
}

void ServerBlock::cleanPaths()
{
	// clean root path
	if (!_root.empty() && _root != "/" && _root[_root.size() - 1] == '/')
		_root.erase(_root.size() - 1);

	// clean all error pages path
	for (std::map<int, std::string>::iterator it = _errorPages.begin(); it != _errorPages.end(); ++it){
		if (it->second != "/" && it->second[it->second.size() - 1] == '/')
			it->second.erase(it->second.size() - 1);
	}

	// clean all Location path
	std::vector<Location>::iterator it;
	for (it = _locations.begin(); it != _locations.end(); ++it)
	{
		it->cleanPaths();
	}
}

bool ServerBlock::isStartBlockLocation(std::vector<std::string>& tokens)
{
	return (tokens.size() == 3 && tokens[0] == "location" && tokens[2] == "{");
}

void ServerBlock::checkDoubleLine()
{
	std::map<std::string, int>::iterator it;

	for (it = _counterView.begin(); it != _counterView.end(); ++it)
		if (it->second > 1)
			Logger::log(FATAL, "Duplicate line in server context: %s", it->first.c_str());
}


void ServerBlock::checkDoubleLocation()
{
	std::vector<Location>::iterator it;
	std::vector<Location>::iterator it2;

	for (it = _locations.begin(); it != _locations.end(); ++it)
	{
		for (it2 = it + 1; it2 != _locations.end(); ++it2)
		{
			if (it->getPath() == it2->getPath())
				Logger::log(FATAL, "Duplicate location: \"%s\" in file: %s", it->getPath().c_str(), _filename.c_str());
		}
	}
}

bool ServerBlock::isValidLineServer(std::vector<std::string>& tokens, std::string& key, std::ifstream &configFile)
{
	if (tokens.size() < 2)
		return false;
	if (isStartBlockLocation(tokens))
	{
		Location location(_filename);
		addLocation(location.getLocationConfig(configFile, tokens[1]));
	}
	else if (key == "listen" && tokens.size() == 2)
		addListen(tokens[1]);
	else if (key == "server_name")
		addServerName(tokens);
	else if (key == "index")
		addIndexes(tokens);
	else if (key == "root" && tokens.size() == 2)
		setRoot(tokens[1]);
	else if (key == "client_max_body_size" && tokens.size() == 2)
		setClientMaxBodySize(tokens[1]);
	else if (key == "error_page" && tokens.size() == 3)
		addErrorPages(std::atoi(tokens[1].c_str()), tokens[2]);
	else
		return (false);
	return (true);
}

ServerBlock ServerBlock::getServerConfig(std::ifstream &configFile)
{
	std::string line;
	std::vector<std::string> tokens;
	std::string key;
	bool isCloseServer = false;

	while (std::getline(configFile, line))
	{
		ConfigParser::countLineFile++;
		line = Utils::trimLine(line);
		if (line.empty() || line[0] == '#')
			continue;
		tokens = Utils::split(line, " ");
		key = tokens[0];
		if (key[0] == '}' && key.size() == 1 && tokens.size() == 1){
			isCloseServer = true;
			break;
		}
		else if (isValidLineServer(tokens, key, configFile))
			continue ;
		else
			Logger::log(FATAL, "Invalid line: \"%s\" in file: %s:%d", line.c_str(), _filename.c_str(), ConfigParser::countLineFile);
	}
	if (isCloseServer == false && ConfigParser::countLineFile == 0)
		Logger::log(FATAL, "Missing } in file %s:%d", _filename.c_str(), ConfigParser::countLineFile);
	checkDoubleLine();
	setDefaultValue();
	checkDoubleLocation();
	cleanPaths();
	return (*this);
}