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
		// _location = rhs._location;
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

void ServerBlock::addIndexes(std::vector<std::string>& token){
	for (size_t i = 1; i < token.size(); i++)
    {
		if (std::find(_index.begin(), _index.end(), token[i]) == _index.end())
			_index.push_back(token[i]);
	}
}