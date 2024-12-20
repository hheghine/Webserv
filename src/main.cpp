#include "Logger.h"
#include "ConfigParser.h"

int main()
{
    try {
        ConfigParser parser;
        parser.parse("/home/heghine/proj/Webserv/config/webserv.conf"); // need to fix this
        // parser.parse("/home/heghine/proj/Webserv/config/multi_server.conf");

        parser.printServers();
    } catch (const std::exception &e){
		return (EXIT_FAILURE);
	}
}