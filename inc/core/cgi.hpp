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
		char					*_argv[3];
		int						_pipe_fd[2];

		// CGI();
		void	urlParser(const std::string& url);
		void	createEnv(std::string str);
		void	convertEnv(/*this->env*/);
		void	cgi(ServerCore *server);

};




}