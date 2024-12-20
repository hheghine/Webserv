#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "Utils.h"
#include "ServerBlock.h"

class ServerBlock;

class ConfigParser
{
public:
    std::map<std::string, std::vector<ServerBlock> > getConfigs() const { return _configs; }
	std::map<std::string, std::vector<ServerBlock> > &getServers() { return _configs; }

    void parse(const std::string& filename);
    void printServers();
    void checkDoubleServerName();
    bool isStartBlockServer(std::vector<std::string> tokens);
    void assignConfigs();

    static	std::vector<std::string>	supportedMethods;
	static	bool						isMethodSupported(std::string method);
	static	std::vector<std::string>	supportedHttpVersions;
	static	bool						isHttpVersionSupported(std::string version);

public:
    static int countLineFile;

private:
    static std::vector<std::string>	getSupportedMethods();
	static std::vector<std::string>	getSupportedHttpVersions();

private:
    std::string                                         _filename;
    std::vector<ServerBlock>                            _servers;
    std::map<std::string, std::vector<ServerBlock> >    _configs;
};

#endif // CONFIGPARSER_H