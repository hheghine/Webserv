#include "responder.hpp"
#include <strings.h>
#include <sstream>
#include <ios>
#include <iostream>
#include <fstream>
using namespace wb;

Responder::Responder()
{}

Responder::Responder(const std::vector<Server *>& _servers)
	: _servers(_servers)
{
	FD_ZERO(&_read_master);
	FD_ZERO(&_write_master);
}

Responder& Responder::operator=(const Responder& other)
{
	this->_servers = other._servers;
	this->_read_master = other._read_master;
	this->_write_master = other._write_master;
	// this->_exception_fd = other._exception_fd;
	this->_fd_host_map = other._fd_host_map;

	return (*this);
}

fd_set& Responder::get_read_master()
{
	return (_read_master);
}

fd_set& Responder::get_write_master()
{
	return (_write_master);
}

void Responder::add_to_map(const int& fd, const u_short& port, const in_addr_t& host)
{
	// _fd_host_map[fd]._fd = fd;
	_fd_host_map[fd]._port = port;
	_fd_host_map[fd]._ip = host;
	_fd_host_map[fd]._code_resp = 200;
}

bool Responder::ready_to_send(int fd)
{
	return (_fd_host_map[fd]._status == SEND || _fd_host_map[fd]._status == SENDBODY);
}

void Responder::action(std::string& response, int fd)
{
	int status = _fd_host_map[fd]._status;

	switch(status)
	{
		case NONE:
		// std::cout << "ya zdeeeesss\n";
			response = start_session(fd);
			break ;
		case SEND:
			break ;
		case SENDBODY:
			break ;
	}
}

std::string Responder::start_session(int fd)
{
	fd_data& data = _fd_host_map[fd];

	data._fd = fd;
	data._response = "";
	bzero(_buff, BUFFER);
	data._bytes_read = recv(fd, &_buff, BUFFER, 0);

	if (data._bytes_read <= 0)
	{
		FD_CLR(fd, &_read_master);
		close(fd);
		std::cout << GRN << "fd [ " << fd << " ] closed !" << CRST << std::endl;
		return "";
	}
	std::cout << "\nREQUEST >>>>>>>>>>>>>>>>>>>>\n" << _buff << std::endl;

	return (parse_html_request(data, _buff));
}

std::string read_index_html_file(const std::string& root, const std::string& path)
{
	printf ("Root is '%s' and index.html path is '%s'\n", root.c_str(), path.c_str());
	std::ifstream file((root + path + std::string("/index.html")).c_str());
	if (!file.is_open()) {
		throw std::runtime_error("Unable to open HTML file");
	}
	std::stringstream buffer;
	buffer << file.rdbuf();
	return (buffer.str());
}

std::string Responder::parse_html_request(fd_data& data, const std::string& buffer)
{
	std::cout << "\n\nPARSED REQUEST >>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
	std::stringstream ss(buffer);
	std::string tmp;

	ss >> data._request_type >> data._file_path >> data._protocol;

	std::cout << "REQ: " << data._request_type << std::endl;
	std::cout << "PATH: " << data._file_path << std::endl;
	std::cout << "HTTP PROTOCOL: " << data._protocol << std::endl;

	ss >> tmp;
	tmp.clear();
	ss >> tmp;
	std::string ip = utils::extract_str_before(tmp, ':');
	data._ip = inet_addr(ip.c_str());

	std::string port = utils::extract_str_after(tmp, ':');
	data._port = htons(utils::extract_port(port));

	std::cout << ip << " " << data._ip << " " << port << " " << data._port << std::endl;
	// data._ip = inet_addr(ip.c_str());
	// std::cout << ip << " " << data._ip << " " << port << " " << data._port << std::endl;
	std::cout << data._file_path << std::endl;
	if (data._request_type == "GET")
	{
		std::string resp;
		std::stringstream	ssfile; 
		if (data._file_path != "/")
		{
			std::cout << data._file_path.substr(1).c_str() << std::endl;
			std::ifstream		file(("www" + data._file_path).c_str());
			ssfile << file.rdbuf();
			resp = ssfile.str();
		}
		else
		{
			std::cout << this->_servers.size() << std::endl;
			// std::cout << this->_servers[0]->_root<< std::endl;
			printf ("Server root is '%s'\n", this->_servers[0]->_root.c_str());
			// std::ifstream		file((this->_servers[0]->_root + "www/index.html").c_str());
			// ssfile << file.rdbuf();
			resp = read_index_html_file(this->_servers[0]->_root + "www/",  data._file_path);
		}
		// std::cout << "ssfile parunalkutyun: '" << ssfile.str() << "'" << std::endl;
		return (resp);
	}
	return ("");


}

