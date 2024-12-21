#ifndef CLIENT_H
#define CLIENT_H

#include <netinet/in.h>
#include <sys/socket.h>
#include <ctime>

#include "Socket.h"

#define CLIENT_READ_BUFFER_SIZE 2*4096

class Client
{
public:
    Client(int fd, Socket* socket);
    ~Client();

public:
    // handleRequest
    // handleResponse
    // reset

    // checkCgi

    // handleClientDisconnection

    time_t 		getLastActivity() const { return _lastActivity; }
	void		updateLastActivity() { _lastActivity = time(NULL); }

private:
    int     _fd;
    Socket* _socket;
    time_t  _lastActivity;
    // Request
    // Response
};

#endif // CLIENT_H