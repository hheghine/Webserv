#include "server_core.hpp"

namespace wb
{

class CGI
{
	public:
		CGI(const std::string& url);
		~CGI();
	public:
		std::vector<char *>		_envVec;
		char					**_env;
		int						_pipe_fd[2];
		char					*_argv[3];

		// CGI();
		void	convert(/*this->env*/);
		void	cgi(ServerCore *server);

};




}