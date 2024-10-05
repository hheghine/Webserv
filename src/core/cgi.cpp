#include "cgi.hpp"
#include <sys/wait.h>

using namespace wb;

CGI::CGI(const std::string& url)
{
	// inch vor baner vor /cgi-bin/* arandznana env ic
	this->urlParser(url);
	// this->createEnv();
	
	_argv[0] = (char *)("bin/python3");
	_argv[1] = (char *)("www/cgi-bin/cgi.py");
	_argv[2] = NULL;
	_env = NULL;


}

CGI::~CGI()
{
	if (_argv)
		delete _argv[1];
	// if (_env)
		// for (int i = 0; )
}

char	*str_to_c(const std::string& str)
{
	size_t	i;
	char	*ret = new char[str.size() + 1];

	for (i = 0; i < str.size(); ++i)
		ret[i] = str[i];
	ret[i] = '\0';

	return (ret);
}


void	CGI::createEnv(std::string str)
{
	// SRANQ PETQA LINEN NEW ARAC CHAR* NER
	_envVec.push_back("CONTENT_TYPE=");
	_envVec.push_back("CONTENT_LENGTH=");
	_envVec.push_back("HTTP_COOKIE=");
	_envVec.push_back("HTTP_USER_AGENT=");
	_envVec.push_back("PATH_INFO=");
	_envVec.push_back("QUERY_STRING=");
	_envVec.push_back("REMOTE_ADDR=");
	_envVec.push_back("REMOTE_HOST=");
	_envVec.push_back("REQUEST_METHOD=");
	_envVec.push_back("SCRIPT_FILENAME=");
	_envVec.push_back("SCRIPT_NAME=");
	_envVec.push_back("SERVER_NAME=");
	_envVec.push_back("SERVER_SOFTWARE=");
	// SRANQ PETQA LINEN NEW ARAC CHAR* NER


	std::cout << "str = '" << str << "'\n";
	size_t pos = str.find('&');
	while (pos != str.npos)
	{
		std::string	envVar = str.substr(0, pos);
		_envVec.push_back(str_to_c(envVar));
		// std::cout << "env new andam is = '" << a << "'\n";
		// std::string bef = utils::extract_str_before(a, '=');
		// std::string aft = utils::extract_str_after(a, '=');
		// char *p = str_to_c(bef + aft);
		// str = str.substr(pos + 1);
		str.erase(0, pos + 1);
		std::cout << "str after ktr = '" << str << "'\n";
		// str.erase()
		pos = str.find('&');
	}
	if (str != "")
		_envVec.push_back(str_to_c(str));
}

void	CGI::convertEnv()
{
	size_t	envSize = this->_envVec.size();
	size_t it;

	if (_env)
		delete[] _env;

	_env = new char*[envSize + 1];

	for (it = 0; it < envSize; ++it)
		this->_env[it] = _envVec[it];
	this->_env[it] = NULL;
	//////////////////////////////
}

void	CGI::urlParser(const std::string& url)
{
	std::cout << "url is '" << url << "'\n";
	// only if in url exists cgi-bin

	size_t	pos = url.find('?');

	// animast if vortev dusy anverj loopum stugelu enq ete cgi-bin ka uxarkenq stex
	if (pos != url.npos)
	{
		// std::cout << "print '" << url.substr(0, pos).c_str() << "'" << std::endl;
		// std::string script = std::string(url.c_str() + pos + 8);
		this->_argv[1] = str_to_c(url.substr(0, pos));
		this->createEnv(url.substr(pos + 1));
		// this->
		// std::cout << "script name is '" << _argv[1] << "'" << std::endl;
	}
	else
	{
		this->_argv[1] = str_to_c(url);
	}
}

void	wb::cgiParse(wb::ServerCore *server, /*request parser*/const std::string& url)
{
	CGI		*cgi = new CGI(url);
	int		state = 0;
	pid_t	cpid;

	if (pipe(cgi->_pipe_fd) < 0)
		throw std::runtime_error("Pipe failed");
	cpid = fork();
	if (cpid == 0)
	{
		cgi->urlParser(url);
		// cgi->convert();
		// if (dup2(cgi->_pipe_fd[1], STDOUT_FILENO) < 0)
		// {
		// 	std::cout << "Dup2 failed" << std::endl;
		// 	exit (1);
		// }
		
		// inch vor tex FD_CLOEXEC xckel
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