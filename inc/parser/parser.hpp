#ifndef PARSER_HPP
# define PARSER_HPP


/*----------- STANDARD LIBRARIES -----------*/
# include <stack>

/*-------------- HEADER FILES --------------*/
# include "webserv.hpp"
# include "server.hpp"
# include "location.hpp"
# include "utils.hpp"

namespace wb
{

/*----------------- ALIASES -----------------*/
typedef std::vector<Server *>::iterator serv_it;

/*--------------- PARSER CLASS ---------------*/
class Parser {
	private:
		std::stack<char> 	_brackets;
		std::string _filename;

	private:
		void parse();
		void parse_server_block(std::ifstream& file);
		void parse_location_block(std::ifstream& file, const svector& location_vec, Location* location);

	public:
		std::vector<Server *> _servers;
		Parser(const std::string& filename);
};

}

#endif