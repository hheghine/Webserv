#include "location.hpp"

using namespace wb;

Location::Location()
	: AServer()
{}

void Location::set_modifier(const svector& line)
{
	svector_const_it it = line.begin() + 1;

	if (line.size() > 3 || it == line.end() || (*it)[0] != '/' \
	|| (it + 1 != line.end() && *(it + 1) != "{"))
		throw std::invalid_argument("syntax error: wrong location block");

	_modifier = *it;
	std::cout << "modifier: " << _modifier << std::endl;
}

void Location::set_redirection(const svector& line)
{
	if (line.size() != 2)
		throw std::invalid_argument("syntax error: wrong location block");
	
	_redirection = *(line.begin() + 1);
	std::cout << "redirection: " << _redirection << std::endl;
}