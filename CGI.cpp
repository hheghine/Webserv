
#include <strings.h>
#include <sstream>
#include <ios>
#include <iostream>
#include <fstream>

int main()
{
	std::string a = "www/favicon.ico";
	std::ifstream b(a.c_str());
	std::stringstream ss;

	ss << b.rdbuf();
	std::cout << ss.str() << std::endl;
	return (0);
}