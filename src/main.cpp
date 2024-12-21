#include "Server.h"

int main()
{
    try
    {
        Server serv;
        serv.getConfigParser().parse("/home/heghine/proj/Webserv/config/webserv.conf");
        serv.getConfigParser().printServers();
    }
    catch (const std::exception &e)
    {
		return (EXIT_FAILURE);
	}
}