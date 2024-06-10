#include "parser.hpp"

Parser::Parser(const std::string& filename, std::vector<Server *>& server)
	: _filename(filename)
	, _servers(server)
{
	parse();
}

void Parser::parse()
{
	std::string::size_type pos = _filename.rfind('.');
	if (pos == std::string::npos)
		throw std::invalid_argument("wrong file format: " + _filename);
	std::string extension = _filename.substr(pos);
	if (extension != ".conf")
		throw std::invalid_argument("wrong file format: " + _filename);

	std::ifstream file(_filename.c_str());
	if (!file.good())
		throw std::invalid_argument("invalid file: " + _filename);

	std::string line;
	while (std::getline(file, line))
	{
		svector vec = utils::split_line(line);

		if (vec.empty() || vec.at(0)[0] == '#')
			continue ;

		if (vec.size() <= 2 && \
		(vec.at(0) == "server" || vec.at(0) == "server{"))
		{
			if (vec.size() > 1 && vec.at(1) != "{")
				throw std::invalid_argument("syntax error: " + line);

			if ((vec.size() == 1 && vec.at(0).find("{") != std::string::npos) \
			|| (vec.size() == 2 && vec.at(1) == "{"))
				_brackets.push('{');
			parse_server_block(file);
		}
		else
			throw std::invalid_argument( "wrong file syntax: " + line);
	}
}

void Parser::parse_server_block(std::ifstream& file)
{
	std::string line;
	_servers.push_back(new Server());
	Server* serv = _servers[_servers.size() - 1];

	while (std::getline(file, line))
	{
		svector vec = utils::split_line(line);

		if (vec.empty() || vec.at(0)[0] == '#')
			continue ;

		if (vec.at(0) == "{" && _brackets.empty())
		{
			if (vec.size() != 1)
				throw std::invalid_argument("syntax error: " + line);
			_brackets.push('{');
			continue ;
		}
		if (vec.at(0) == "}" && vec.size() == 1)
		{
			if (_brackets.empty())
				throw std::invalid_argument("syntax error: mismatched or missing bracket");

			_brackets.pop();
			if (_brackets.empty())
				return ;
			continue ;
		}

		bool match = false;

		switch (vec[0][0])
		{
			case Server::SERVER_NAME :
				if (vec[0] == "server_name")
				{
					match = true;
					serv->set_server_name(vec);
				}
				break ;
			case Server::LISTEN :
				if (vec[0] == "listen")
				{
					match = true;
					serv->set_hosts(vec);
				}
				else if (vec[0] == "location")
				{
					match = true;
					Location* location = new Location();
					serv->_locations.push_back(location);
					parse_location_block(file, vec, location);
				}
				break ;
			case Server::INDEX :
				if (vec[0] == "index")
				{
					match = true;
					serv->set_index(vec);
				}
				break ;
			case Server::ROOT :
				if (vec[0] == "root")
				{
					match = true;
					serv->set_root(vec);
				}
				break ;
			case Server::AUTOINDEX :
				if (vec[0] == "autoindex")
				{
					match = true;
					serv->set_autoindex(vec);
				}
				break ;
			case Server::METHODS :
				if (vec[0] == "methods")
				{
					match = true;
					serv->set_methods(vec);
				}
		}
		if (!match)
			throw std::invalid_argument("syntax error: " + line);
	}
	if (!_brackets.empty())
		throw std::invalid_argument("syntax error: mismatched or missing bracket");
}

void Parser::parse_location_block(std::ifstream& file, const svector& location_vec, Location* location)
{
	location->set_modifier(location_vec);

	bool opened = false;
	bool closed = false;

	if (*(location_vec.end() - 1) == "{")
	{
		opened = true;
		_brackets.push('{');
	}

	std::string line;

	while (std::getline(file, line))
	{
		svector vec = utils::split_line(line);

		if (vec.empty() || vec.at(0)[0] == '#')
			continue ;

		if (vec.at(0) == "{")
		{
			if (opened)
				throw std::invalid_argument("syntax error: mismatched or missing bracket");
			opened = true;
			if (vec.size() != 1)
				throw std::invalid_argument("syntax error: " + line);
			_brackets.push('{');
			continue ;
		}
		if (vec.at(0) == "}" && vec.size() == 1)
		{
			closed = true;
			_brackets.pop();
			break ;
		}

		bool match = false;

		switch (vec[0][0])
		{
			case Location::INDEX :
				if (vec[0] == "index")
				{
					match = true;
					location->set_index(vec);
				}
				break ;
			case Location::AUTOINDEX :
				if (vec[0] == "autoindex")
				{
					match = true;
					location->set_autoindex(vec);
				}
				break ;
			case Location::METHODS :
				if (vec[0] == "methods")
				{
					match = true;
					location->set_methods(vec);
				}
				break ;
			case Location::REDIRECTION :
				if (vec[0] == "redirect")
				{
					match = true;
					location->set_redirection(vec);
				}
				break ;
			case Location::LOCATION :
				if (vec[0] == "location")
				{
					match = true;
					Location* loc = new Location();
					location->_locations.push_back(loc);
					parse_location_block(file, vec, loc);
				}
		}
		if (!match)
			throw std::invalid_argument("syntax error: " + line);
	}
	if (!opened || !closed)
		throw std::invalid_argument("syntax error: mismatched or missing bracket");
}