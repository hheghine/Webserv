#include "server.hpp"

Server::Server()
	: AServer()
	, _max_body_size(300)
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

const hosts_map& Server::get_hosts_map() const
{
	return _hosts;
}

void Server::set_hosts(const svector& line)
{
	if (line.size() != 2)
		throw std::invalid_argument("wrong host syntax");

	svector_const_it it = line.begin() + 1;
	size_t idx = (*it).find(':');

	if (idx != std::string::npos)
	{
		if (idx == (*it).size() - 1)
			throw std::invalid_argument("wrong host syntax");
		std::string ip = utils::extract_str_before(*it, ':');
		utils::ip_check(ip);
		u_short port = utils::extract_port(utils::extract_str_after(*it, ':'));
		_hosts[ip].push_back(port);
		
		add_universal_ports(ip);
	}
	else
	{
		idx = (*it).find('.');
		if (idx != std::string::npos)
		{
			utils::ip_check(*it);
			_hosts[*it].push_back(80);
			add_universal_ports(*it);
		}
		else
		{
			u_short port = utils::extract_port(*it);
			_universal_ports.push_back(port);
			for (hosts_it iter = _hosts.begin(); iter != _hosts.end(); ++iter)
				iter->second.push_back(port);
		}
	}
}

void Server::add_universal_ports(const std::string& ip)
{
	for (std::vector<u_short>::const_iterator it = _universal_ports.begin(); it != _universal_ports.end(); ++it)
	{
		if (std::find(_hosts[ip].begin(), _hosts[ip].end(), *it) == _hosts[ip].end())
			_hosts[ip].push_back(*it);
	}
}

