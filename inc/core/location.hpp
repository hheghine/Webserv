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
		void set_modifier(const svector& line);
		// void set_redirection(const svector& line);

};

#endif