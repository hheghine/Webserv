#include "a_server.hpp"
#include <filesystem>

using namespace wb;

AServer::AServer()
	: _get(false)
	, _post(false)
	, _delete(false)
	, _autoindex(false)
{}

AServer::~AServer()
{
	for (location_it it = _locations.begin(); it != _locations.end(); ++it)
		delete *it;
}

void AServer::set_root(const svector& line)
{
	svector_const_it it = line.begin() + 1;

	if (line.size() != 2)
	{
		throw std::invalid_argument("root: syntax error");
		return ;
	}
	if (!utils::is_directory(*it))
	{
		throw std::invalid_argument("root: not a directory");
		return ;
	}
	_root = "www/" + *it;
	std::cout << "root: " << _root << std::endl;
}

void AServer::set_index(const svector& line)
{
	svector_const_it it = line.begin() + 1;

	if (it + 1 != line.end())
	{
		throw std::invalid_argument("index: syntax error");
		return ;
	}

	std::string fpath = "www/" + *it;

	if (utils::file_exists(fpath, R_OK))
	{
		std::string::size_type pos = (fpath).rfind('.');
		if (pos == std::string::npos)
		{
			throw std::invalid_argument("wrong file format: " + *it);
			return ;
		}
		std::string extension = (fpath).substr(pos);
		if (extension != ".html")
		{
			throw std::invalid_argument("wrong file format: " + *it);
			return ;
		}
		else
		{
			_index = fpath;
			std::cout << "index: " << _index << std::endl;
			return ;
		}
	}
	throw std::invalid_argument(("non-existent file: ") + *it);
}

void AServer::set_methods(const svector& line)
{
	for (svector_const_it it = line.begin() + 1; it != line.end(); ++it)
	{
		if (*it == "GET")
			_get = true;
		else if (*it == "POST")
			_post = true;
		else if (*it == "DELETE")
			_delete = true;
		else
		{
			throw std::invalid_argument("invalid method");
			return ;
		}
	}
	std::cout << "get, post, delete: " << _get << _post << _delete << std::endl;
}

void AServer::set_autoindex(const svector& line)
{
	svector_const_it it = line.begin() + 1;

	if (line.size() != 2)
		throw std::invalid_argument("syntax error: " + line.at(0));

	if (*it == "on" || *it == "ON")
		_autoindex = true;
	else if (*it == "off" || *it == "OFF")
		_autoindex = false;
	else
		throw std::invalid_argument("syntax error: unknown character: " + *it);
	std::cout << "autoindex: " << _autoindex << std::endl;
}