#include "parser.hpp"

Parser::Parser(const std::string& filename)
{
	try {
		lets_go(filename);
	} catch (const std::exception& e) {
		std::cout << RED << "[ ✘ ] " << e.what() << std::endl;
	}
}

Parser::~Parser()
{
	for (serv_it it = _servers.begin(); it != _servers.end(); ++ it)
		delete *it;
}

void Parser::lets_go(const std::string& filename)
{
	std::string::size_type pos = filename.rfind('.');
	if (pos == std::string::npos)
		throw std::invalid_argument("wrong file format: " + filename);
	std::string extension = filename.substr(pos);
	if (extension != ".conf")
		throw std::invalid_argument("wrong file format: " + filename);

	std::ifstream file(filename.c_str());
	if (!file.good())
		throw std::invalid_argument("invalid file: " + filename);

	std::string line;
	while (std::getline(file, line))
	{
		svector vec = utils::split_line(line);

		if (vec.empty() || vec.at(0)[0] == '#')
			continue ;

		if (vec.size() <= 2 && \
		(vec.at(0) == "server" || vec.at(0) == "server{"))
		{
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
		if (!g_error.empty())
			throw std::runtime_error(g_error);

		svector vec = utils::split_line(line);

		if (vec.empty() || vec.at(0)[0] == '#')
			continue ;

		if (line[0] == '{' && _brackets.empty())
		{
			if (vec.size() != 1)
				throw std::runtime_error("syntax error: " + line);
			_brackets.push('{');
			continue ;
		}
		if (line[0] == '}' && vec.size() == 1)
		{
			_brackets.pop();
			continue ;
		}
		if (vec[0] == "index")
		{
			serv->set_index(vec);
			continue ;
		}
		if (vec[0] == "root")
		{
			serv->set_root(vec);
			continue ;
		}
		throw std::runtime_error("syntax error: " + line);
	}
	if (!_brackets.empty())
		throw std::invalid_argument("syntax error: mismatched or missing bracket");
}