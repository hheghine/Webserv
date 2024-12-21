#include "Client.h"

Client::Client(int fd, Socket* socket)
    : _fd(fd)
    , _socket(socket)
    , _lastActivity(time(NULL))
{}

Client::~Client()
{
    if (_fd < 0)
        Utils::protectedCall(close(_fd), "[~Client] Failed to close client socket", false);
}