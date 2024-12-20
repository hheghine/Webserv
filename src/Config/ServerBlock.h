#ifndef SERVERBLOCK_H
#define SERVERBLOCK_H

#define BS_DEFAULT_CLIENT_MAX_BODY_SIZE 1048576 // 1MB

#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <algorithm>
#include <string>

#include "Logger.h"
#include "Utils.h"
#include "ListenConfig.h"
#include "Location.h"
#include "ConfigParser.h"

class ListenConfig;
class ConfigParser;
class Location;

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
    std::vector<Location>               _locations;      

    std::string                         _filename;
    std::map<std::string, int>          _counterView;

public:
    ServerBlock getServerConfig(std::ifstream& file);

    bool isServerNamePresent(std::vector<std::string>& otherNames);
    bool isValidLineServer(std::vector<std::string>& tokens, std::string& key, std::ifstream &configFile);
    bool isStartBlockLocation(std::vector<std::string>& tokens);

    const std::map<int, std::string> &getErrorPages() const { return _errorPages; }
	const std::vector<std::string> &getServerNames() const { return _serverNames; }
	std::vector<Location>* getLocations() { return &_locations; }
	const std::string &getRoot() const { return _root; }
	unsigned long long getClientMaxBodySize() const { return _clientMaxBodySize; }
	const std::map<std::string, ListenConfig> &getListens() const { return _listen; }
	const std::vector<std::string> &getIndexes() const { return _index; }

    void printServer();
	void printListens();
	void printPair(const std::string& label, const std::string& value);
	void printInt(const std::string& label, int value);
	void printVector(const std::string& label, const std::vector<std::string>& vec);
	void printMap(const std::string& label, const std::map<int, std::string>& map);

private:
    void setClientMaxBodySize(std::string clientMaxBodySize);
	void setRoot(const std::string &root) { _root = root; _counterView["root"]++; }
	void setDefaultValue();
	void setLocations(const std::vector<Location> &locations) { _locations = locations; }
	void setErrorPages(const std::map<int, std::string> &errorPage) { _errorPages = errorPage; }

	void addErrorPages(int errorCode, std::string file);
	void addListen(std::string& token);
	void addServerName(std::vector<std::string>& token);
	void addIndexes(std::vector<std::string>& token);
    void addLocation(const Location& locations) { _locations.push_back(locations); }

    void checkDoubleLine();
	void incrementCounter(const std::string &key) { _counterView[key]++; }
	void checkDoubleLocation();
	void cleanPaths();

};



#endif // SERVERBLOCK_H