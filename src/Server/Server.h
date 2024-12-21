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
#include "Socket.h"
#include "Client.h"

typedef std::map<int, Socket*>::iterator socket_it;
typedef std::map<int, Client*>::iterator client_it;


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

public:
    void init();
    void run();
    void stop();

    int                     getState(void) const { return _state; }
	int                     getEpollFD(void) const { return _epollFd; }
	ConfigParser&           getConfigParser(void) { return _parser; }
	std::map<int, Socket*>  getSockets(void) const { return _sockets; }
	std::map<int, Client*>  getClients(void) const { return _clients; }
	Socket*                 getSocket(int fd) { return _sockets[fd]; }
	Client*                 getClient(int fd) { return _clients[fd]; }

private:
    void setServerState(ServerState state);
    void setEpollFd(int epollFd) { _epollFd = epollFd; }

    // checkTimeout
    // handleEvent
    // handleClientConnection(int fd)
    // handleClientDisconnection(int fd)

private:
    int                      _state;
    int                      _epollFd;
    ConfigParser             _parser;
    std::map<int, Socket*>   _sockets;
    std::map<int, Client*>   _clients;
};

#endif // SERVER_H