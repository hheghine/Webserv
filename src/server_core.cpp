#include "server_core.hpp"

ServerCore::~ServerCore()
{
	for (std::vector<Server *>::iterator it = _servers.begin(); it != _servers.end(); ++ it)
		delete *it;
}

void ServerCore::_create_listen_sockets()
{
	int size = 0;


	for (std::vector<Server *>::iterator it = _servers.begin(); it != _servers.end(); ++it)
		size += ((*it)->_ports.size());

	_listen_sockets.reserve(size);
	for (int i = 0; i < size; ++i)
		_init_listen_socket(i);
}

void ServerCore::_init_listen_socket(int i)
{
	struct sockaddr address;
	struct sockaddr_in& addressIn = reinterpret_cast<struct sockaddr_in&>(address);

    memset(reinterpret_cast<char *>(&address), 0, sizeof(struct sockaddr));

// 	addressIn.sin_family = AF_INET;
//     addressIn.sin_port = _ports[i].getPort();
//     addressIn.sin_addr.s_addr = _ports[i].getHost();


//     _listenSockets[i].port = addressIn.sin_port;
//     _listenSockets[i].host = addressIn.sin_addr.s_addr;
//     _listenSockets[i].socket = socket(AF_INET, SOCK_STREAM, 0);

// std::cout << "listen socket " << _listenSockets[i].socket << " addr " << addressIn.sin_port << " " << addressIn.sin_addr.s_addr <<  std::endl;


//     int opt = 1;
//     setsockopt(_listenSockets[i].socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

//     if (::bind(_listenSockets[i].socket, &address, sizeof(address))) {
//         perror("bind");
//         exit(1);
//     }

//     if (listen(_listenSockets[i].socket, 32)) {
//         perror("listen");
//         exit(1);
//     }

//     FD_SET(_listenSockets[i].socket, &_responder.getMaster());

//     if (_listenSockets[i].socket > _num) {
//         _num = _listenSockets[i].socket;
//     }
}