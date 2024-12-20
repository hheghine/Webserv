#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>
#include <string>
#include <cstdarg>
#include <stdint.h>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <dirent.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <arpa/inet.h>

#include "Logger.h"

namespace Utils
{

std::vector<std::string>    split(std::string s, std::string delimiter);
std::string                 trimLine(std::string &line);
std::string                 unsignedIntToString(unsigned int value);
unsigned long long          strToUll(std::string clientMaxBodySize);
std::string                 ullToStr(unsigned long long ull);
std::string                 intToString(int value);

}

#endif // UTILS_H