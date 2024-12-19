#ifndef LISTENCONFIG_H
#define LISTENCONFIG_H

#include <iostream>
#include <vector>
#include <string>

#include "Logger.h"
#include "Utils.h"


class ListenConfig
{
public:
    ListenConfig();
    ListenConfig(std::string token);
    ~ListenConfig();

public:
    const std::string&  getIp() const { return _ip; }
    unsigned int        getPort() const { return _port; }
    const std::string&  getIpPort() const { return _ip_port; }

private:
    bool checkIpPort();
    bool isNotInRangeIp(std::string str, int j, int i);

private:
    std::string     _ip;
    unsigned int    _port;
    std::string     _ip_port;
};


#endif // LISTENCONFIG_H