#include "location.hpp"

Location::Location()
	: AServer()
{}

void Location::set_modifier(const svector& line)
{
	svector_const_it it = line.begin() + 1;

	if (it == line.end() || (*it)[0] != '/' \
	|| (it + 1 != line.end() && *(it + 1) != "{"))
		throw std::invalid_argument("syntax error: wrong location block");

	_modifier = *it;
}