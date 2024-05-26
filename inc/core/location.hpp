#ifndef LOCATION_HPP
# define LOCATION_HPP

# include "a_server.hpp"

class Location : public AServer {
	private:
		std::string	_modifier;
		std::string _redirection;

	public:
		Location();

	public:
		enum vars {
			INDEX = 105,
			AUTOINDEX = 97,
			METHODS = 109,
			LOCATION = 108,
			REDIRECTION = 114
		};

	public:
		void set_modifier(const svector& line);
		void set_redirection(const svector& line);

};

#endif