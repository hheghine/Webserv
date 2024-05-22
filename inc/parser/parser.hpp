#ifndef PARSER_HPP
# define PARSER_HPP


/*-----------STANDARD LIBRARIES-----------*/
# include <stack>

/*--------------HEADER FILES--------------*/
# include "webserv.hpp"
# include "server.hpp"
# include "utils.hpp"

using namespace wb;

/*-----------------ALIASES-----------------*/
typedef std::vector<Server *>::iterator serv_it;

/*---------------PARSER CLASS---------------*/
class Parser {
	public:
		Parser(const std::string& filename);
		~Parser();

	private:
		std::stack<char> _brackets;
		std::vector<Server *> _servers;
	
	private:
		void lets_go(const std::string& filename);
		void parse_server_block(std::ifstream& file);
};


#endif