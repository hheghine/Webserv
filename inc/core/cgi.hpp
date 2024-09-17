#include "server_core.hpp"

namespace wb
{

class CGI
{
	public:
		std::vector<char *>		_envVec;
		char					**_env;
		int						_pipe_fd[2];
		char					*_argv[3];

		// CGI();
		void	convert(/*this->env*/);
		void	cgi(ServerCore *server);

		CGI(const std::string& url);
};




}