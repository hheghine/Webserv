#ifndef PARSER_HPP
# define PARSER_HPP


/*----------- STANDARD LIBRARIES -----------*/
# include <stack>

/*-------------- HEADER FILES --------------*/
# include "webserv.hpp"
# include "server.hpp"
# include "location.hpp"
# include "utils.hpp"

using namespace wb;

/*----------------- ALIASES -----------------*/
typedef std::vector<Server *>::iterator serv_it;

/*--------------- PARSER CLASS ---------------*/
class Parser {
	private:
		std::stack<char> 	_brackets;

	private:
		void lets_go(const std::string& filename, std::vector<Server *>& _servers);
		void parse_server_block(std::ifstream& file, std::vector<Server *>& _servers);
		void parse_location_block(std::ifstream& file, const svector& location_vec, Location* location);

	public:
		Parser(const std::string& filename, std::vector<Server *>& _servers);
};


#endif