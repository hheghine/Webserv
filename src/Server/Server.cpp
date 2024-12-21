#include "Server.h"

Server::Server()
    : _state(SERVER_STATE_INIT)
    , _epollFd(-1)
{}

Server::~Server()
{
    if (_epollFd > 0)
        Utils::protectedCall(close(_epollFd), "Failed to close epoll instance", false);
    // Delete all the sockets
    for (socket_it it = _sockets.begin(); it != _sockets.end(); ++it)
        delete it->second;
    _sockets.clear();
    // Delete all the clients
    for (client_it it = _clients.begin(); it != _clients.end(); ++it)
        delete it->second;
    _clients.clear();

}

void Server::setServerState(ServerState state)
{
    switch(state)
    {
        case SERVER_STATE_INIT:
            Logger::log(INFO, "Parsing completed");
            break;
        case SERVER_STATE_READY:
            Logger::log(INFO, "Server is ready to run");
            break;
        case SERVER_STATE_RUN:
            Logger::log(INFO, "Server is running");
            break;
        case SERVER_STATE_STOP:
            Logger::log(INFO, "Server is stopping...");
    }
    _state = state;
}