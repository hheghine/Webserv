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
	_root = *it;
}

void AServer::set_index(const svector& line)
{
	svector_const_it it = line.begin() + 1;

	if (it + 1 != line.end())
	{
		g_error = "root: syntax error";
		return ;
	}
	if (utils::file_exists(*it))
	{
		std::string::size_type pos = (*it).rfind('.');
		if (pos == std::string::npos)
		{
			g_error = "wrong file format: " + *it;
			return ;
		}
		std::string extension = (*it).substr(pos);
		if (extension != ".html")
		{
			g_error = "wrong file format: " + *it;
			return ;
		}
		else
		{
			_index = *it;
			return ;
		}
	}
	g_error = ("non-existent file: ") + *it;
}