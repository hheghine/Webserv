#ifndef SERVERBLOCK_H
#define SERVERBLOCK_H

#define BS_DEFAULT_CLIENT_MAX_BODY_SIZE 1048576 // 1MB

#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <algorithm>

#include "Logger.h"
#include "ListenConfig.h"

class ListenConfig;

class ServerBlock
{
public:
    ServerBlock(std::string filename);
    ServerBlock();
    ServerBlock(const ServerBlock& rhs);

    ServerBlock& operator=(const ServerBlock& rhs);

private:
    std::map<std::string, ListenConfig> _listen;
    std::vector<std::string>            _serverNames;
    std::vector<std::string>            _index;
    std::string                         _root;
    unsigned long long                  _clientMaxBodySize;
    std::map<int, std::string>          _errorPages;
    // locations

    std::string                         _filename;
    std::map<std::string, int>          _counterView;

public:
    ServerBlock getServerConfig(std::ifstream& file);

private:
    void setClientMaxBodySize(std::string clientMaxBodySize);
	void setRoot(const std::string &root) { _root = root; _counterView["root"]++; }
	void setDefaultValue();
	// setLocations
	void setErrorPages(const std::map<int, std::string> &errorPage) { _errorPages = errorPage; }

	void addErrorPages(int errorCode, std::string file);
	void addListen(std::string& token);
	void addServerName(std::vector<std::string>& token);
	void addIndexes(std::vector<std::string>& token);
    // addLocation
};



#endif // SERVERBLOCK_H