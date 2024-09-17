#include <sys/wait.h>
#include <stdio.h>
#include <errno.h>

char **createEnv(int *server)
{
	char **env;

	env = new char*[14];

	env[0]	= (char *)"CONTENT_TYPE=";
	env[1]	= (char *)"CONTENT_LENGTH=";
	env[2]	= (char *)"HTTP_COOKIE=";
	env[3]	= (char *)"HTTP_USER_AGENT=";
	env[4]	= (char *)"PATH_INFO=";
	env[5]	= (char *)"QUERY_STRING=";
	env[6]	= (char *)"REMOTE_ADDR=";
	env[7]	= (char *)"REMOTE_HOST=";
	env[8]	= (char *)"REQUEST_METHOD=";
	env[9]	= (char *)"SCRIPT_FILENAME=";
	env[10] = (char *)"SCRIPT_NAME=";
	env[11] = (char *)"SERVER_NAME=";
	env[12] = (char *)"SERVER_SOFTWARE=";
	env[13] = NULL;

	return (env);

}

int main()
{
	int		state = 0;
	pid_t	cpid;
	int *server;

	cpid = fork();
	if (cpid == 0)
	{
		char **env = createEnv(server);
		char **arg = new char*[2];

		arg[0] = (char *)("/usr/bin/python3");
		arg[1] = (char *)("www/cgi-bin/cgi.py");
		arg[2] = NULL;

		// printf("nixuyasebe\n");
		int err = execve (*arg, arg, env);
		// int err = execve (argv[0], argv, env);
		perror("ya");
		// printf("%d\n", errno);
	}
	waitpid(cpid, &state, 0);	
}