#include "a_server.hpp"
#include <filesystem>

std::string wb::g_error;

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

	if (it + 1 != line.end())
	{
		g_error = "root: syntax error";
		return ;
	}
	if (!utils::is_directory(*it))
	{
		g_error = "root: not a directory";
		return ;
	}
	_root = "www/" + *it;
}

void AServer::set_index(const svector& line)
{
	svector_const_it it = line.begin() + 1;

	if (it + 1 != line.end())
	{
		g_error = "index: syntax error";
		return ;
	}

	std::string fpath = "www/" + *it;

	if (utils::file_exists(fpath))
	{
		std::string::size_type pos = (fpath).rfind('.');
		if (pos == std::string::npos)
		{
			g_error = "wrong file format: " + *it;
			return ;
		}
		std::string extension = (fpath).substr(pos);
		if (extension != ".html")
		{
			g_error = "wrong file format: " + *it;
			return ;
		}
		else
		{
			_index = fpath;
			return ;
		}
	}
	g_error = ("non-existent file: ") + *it;
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
			g_error = "invalid method";
			return ;
		}
	}
}