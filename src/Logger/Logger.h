#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <unistd.h>
#include <cstdio>
#include <stdlib.h>
#include <fcntl.h>
#include <ctime>
#include <cerrno>
#include <cstring>
#include <string>
#include <sys/stat.h>
#include <map>
#include <stdarg.h>
#include <vector>

#include "Constants.h"

/* Default parameters */
const bool DEFAULT_LOG_STATE = true;
const bool DEFAULT_LOG_FILE_STATE = false;
const bool DEFAULT_LOG_DEBUG_STATE = false;

const std::string logLevelString[] = { "FATAL", "ERROR", "WARNING", "INFO", "TRACE", "DEBUG" };
const std::string logLevelColor[] = { C_RED, C_RED, C_YELLOW, C_GREEN, C_MAGENTA, C_CYAN };

enum LogLevel
{
    FATAL = 0,
    ERROR,
    WARNING,
    INFO,
    TRACE,
    DEBUG
};

class Logger
{
public:
    /* MAIN */
    static void log(LogLevel lvl, const char* msg, ...);

    /* SETTERS */
    static void setLogState(bool state);
    static void setLogFileState(bool state);
    static void setLogDebugState(bool state);

    static std::string getLogFileName();

private:
    static std::string generateLogFileName();
	static std::string formater(LogLevel lvl, const char *msg, std::string time, bool colored = true);
	static void printLog(LogLevel lvl, const char *msg, std::string time);
	static void writeLogInFile(LogLevel level, const char *msg, std::string time);

private:
    static bool _logState;
    static bool _logFileState;
    static bool _logDebugState;
    static std::string _logFileName;
};

#endif // LOGGER_H