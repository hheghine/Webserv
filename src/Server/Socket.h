#ifndef SOCKET_H
#define SOCKET_H

#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include "ServerBlock.h"

#define BACKLOGS 100

class Socket
{
public:
    Socket();
    Socket(int fd, std::string ip, unsigned int port, std::vector<ServerBlock>* servers);
    Socket(const Socket& other);
    ~Socket();

    Socket& operator=(const Socket& other);

public:
    std::string                 getIp(void) const { return _ip; }
	unsigned int                getPort(void) const { return _port; }
	int                         getFd(void) const { return _fd; }
	std::vector<ServerBlock>*   getServers(void) const { return _servers; }
	struct sockaddr_in          getAddr(void) const { return _addr; }

private:
    int                         _fd;
    std::string                 _ip;
    unsigned int                _port;
    std::vector<ServerBlock>*   _servers;
    struct sockaddr_in          _addr;
};

#endif // SOCKET_H