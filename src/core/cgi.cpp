#include "cgi.hpp"
#include <sys/wait.h>

using namespace wb;

CGI::CGI(const std::string& url)
{
	// inch vor baner vor /cgi-bin/* arandznana env ic
	
	_argv[0] = (char *)("/usr/bin/python3");
	_argv[1] = (char *)("www/cgi-bin/cgi.py");
	_argv[2] = NULL;
	_env = NULL;

}

// CGI::~CGI()
// {

// }

// char **createEnv(wb::ServerCore *server)
// {
// 	char **env;

// 	env = new char*[13];

// 	env[0]	= (char *)"CONTENT_TYPE=";
// 	env[1]	= (char *)"CONTENT_LENGTH=";
// 	env[2]	= (char *)"HTTP_COOKIE=";
// 	env[3]	= (char *)"HTTP_USER_AGENT=";
// 	env[4]	= (char *)"PATH_INFO=";
// 	env[5]	= (char *)"QUERY_STRING=";
// 	env[6]	= (char *)"REMOTE_ADDR=";
// 	env[7]	= (char *)"REMOTE_HOST=";
// 	env[8]	= (char *)"REQUEST_METHOD=";
// 	env[9]	= (char *)"SCRIPT_FILENAME=";
// 	env[10] = (char *)"SCRIPT_NAME=";
// 	env[11] = (char *)"SERVER_NAME=";
// 	env[12] = (char *)"SERVER_SOFTWARE=";

// 	return (env);

// }

void	CGI::convert()
{
	size_t	envSize = this->_envVec.size();
	size_t it;

	if (_env)
		delete[] _env;

	_env = new char*[envSize + 1];

	for (it = 0; it < envSize; ++it)
	{
		this->_env[it] = _envVec[it];
	}

	this->_env[it] = NULL;
	//////////////////////////////
}

void	wb::cgiParse(wb::ServerCore *server, /*request parser*/const std::string& url)
{
	CGI		*cgi = new CGI(url);
	int		state = 0;
	pid_t	cpid;

	if (pipe(cgi->_pipe_fd) < 0)
	{
		std::cout << "Pipe failed" << std::endl;
		exit (1);
	}

	cpid = fork();
	if (cpid == 0)
	{
		cgi->convert();

		// argv[0] = (char *)("/usr/bin/python3");
		// argv[1] = (char *)("www/cgi-bin/cgi.py");
		
		// if (dup2(cgi->_pipe_fd[1], STDOUT_FILENO) < 0)
		// {
		// 	std::cout << "Dup2 failed" << std::endl;
		// 	exit (1);
		// }

		if (execve (cgi->_argv[0], cgi->_argv, cgi->_env) < 0)
		{
			perror("");
			std::cout << "Execve failed" << std::endl;
			exit (1);
		}
	}

	// Timeout with select

	waitpid(cpid, &state, 0);
	WEXITSTATUS(state);
	if (state == 1)
	{
		// CGI error
		;
	}	
	delete cgi;
}