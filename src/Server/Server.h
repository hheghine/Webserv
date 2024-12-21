#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <arpa/inet.h>
#include <sys/epoll.h>

#include "ConfigParser.h"
#include "ServerBlock.h"
#include "Utils.h"

enum ServerState
{
    SERVER_STATE_INIT = 0,
    SERVER_STATE_READY,
    SERVER_STATE_RUN,
    SERVER_STATE_STOP
};

class Server
{
public:
    Server();
    ~Server();

    void init();
    void run();
    void stop();

private:
    // void setState(ServerState state);
    void setEpollFd(int epollFd) { _epollFd = epollFd; }

private:
    int                      _state;
    int                      _epollFd;
    ConfigParser             _parser;
    // std::map<int, Socket*>   _sockets;
    // std::map<int, Client*>   _clients;
};

#endif // SERVER_H