#ifndef A_SERVER_HPP
# define A_SERVER_HPP

# include "webserv.hpp"
using namespace wb;

class AServer {
	private:
		std::string	_root;
		std::string	_index;
		// svector		_error_pages;
		bool _get;
		bool _post;
		bool _delete;
		bool _autoindex;
		std::vector<AServer* >	_locations;

	public:
		AServer();
		virtual ~AServer() = 0;

		void	set_root(const svector& line);
		void	set_index(const svector& line);
		// void	set_error_pages(const svector& line);
		// void	set_methods(const svector& line);
		// void	set_autoindex(const svector& line);
		// void	set_location(const svector& vec);

};

typedef std::vector<AServer *>::iterator location_it;

#endif