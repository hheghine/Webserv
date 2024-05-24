#include "server.hpp"

Server::Server()
	: AServer()
{}

void Server::set_server_name(const svector& line)
{
	svector_const_it it = line.begin() + 1;

	if (it == line.end())
		throw std::invalid_argument("syntax error: " + line.at(0));

	if (it + 1 != line.end())
		throw std::invalid_argument("syntax error: " + line.at(0));

	_server_name = line.at(1);
	std::cout << "server_name: " << _server_name << std::endl; 
}

void Server::set_ports(const svector& line)
{
	svector_const_it it = line.begin() + 1;

	std::cout << "ports: ";
	for(; it != line.end(); ++it)
	{
		_ports.push_back(utils::to_int(*it));
		std::cout << utils::to_int(*it) << " ";
	}
	std::cout << std::endl;
}