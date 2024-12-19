#include "Logger.h"

/*
 * @brief The state of the logger
 *
 * ON : The logger is on
 * OFF : The logger is off
 */
bool Logger::_logState = DEFAULT_LOG_STATE;

/*
 * @brief The state of the file logger
 *
 * true : The logger save the logs in a file
 * false : The logger doesn't save the logs in a file
 */
bool Logger::_logFileState = DEFAULT_LOG_FILE_STATE;

/*
 * @brief The state of the debug logger
 *
 * true : The logger save the debug logs
 * false : The logger doesn't save the debug logs
 */
bool Logger::_logDebugState = DEFAULT_LOG_DEBUG_STATE;

/*
 * @brief The file name
 */
std::string Logger::_logFileName = Logger::generateLogFileName();


std::string Logger::generateLogFileName()
{
	std::time_t t = std::time(NULL);
	char buffer[80];
	std::strftime(
        buffer,
        sizeof(buffer),
        "webserv_%Y-%m-%d_%H-%M-%S.log",
        std::localtime(&t)
    );

	return (std::string(buffer));
}

std::string Logger::formatter(LogLevel lvl, const char *msg, std::string time, bool colored)
{
	std::string formatedMsg;

	if (colored == true)
		formatedMsg += logLevelColor[lvl];
	formatedMsg += "[" + logLevelString[lvl] + "]   ";
	formatedMsg += time + " : " + msg;
	if ((lvl == FATAL) && errno != 0)
		formatedMsg += ": " + static_cast<std::string>(std::strerror(errno));
	if (colored == true)
		formatedMsg += C_RESET;

	return (formatedMsg);
}

void Logger::printLog(LogLevel lvl, const char *msg, std::string time)
{
	std::cout << formatter(lvl, msg, time) << std::endl;
}

void Logger::writeLogInFile(LogLevel level, const char *msg, std::string time)
{
	// Create directory if doesn't exist
	if (mkdir("logs", 0777) == -1 && errno != EEXIST)
	{
		std::cerr << "Error: " << std::strerror(errno) << std::endl;
		return;
	}
	int file = open(("logs/" + _logFileName).c_str(), O_CREAT | O_WRONLY | O_APPEND, 0666);
	std::string log = formatter(level, msg, time, false);
	write(file, log.c_str(), log.size());
	write(file, "\n", 1);
	close(file);
}

void Logger::log(LogLevel lvl, const char *msg, ...)
{
	// Check if the logger is on
	if (_logState == false || (lvl == DEBUG && _logDebugState == false))
		return;

	// Create a buffer
	const int initialBufferSize = 1024;
	std::vector<char> buffer(initialBufferSize);

	va_list args;
	va_start(args, msg);
	int size = vsnprintf(buffer.data(), buffer.size(), msg, args);
	va_end(args);

	// Handling error
	if (size < 0)
	{
		return;
	}

	// Resize the buffer if needed
	while (size >= static_cast<int>(buffer.size()))
	{
		buffer.resize(buffer.size() * 2);
		va_start(args, msg);
		size = vsnprintf(buffer.data(), buffer.size(), msg, args);
		va_end(args);
	}

	// Get the current time
	std::time_t t = std::time(NULL);
	char timeBuffer[80];
	std::strftime(
        timeBuffer,
        sizeof(timeBuffer),
        "%Y-%m-%d %H:%M:%S",
        std::localtime(&t)
    );

	// Print the log
    printLog(lvl, buffer.data(), timeBuffer);

	if (_logFileState == true)
		writeLogInFile(lvl, buffer.data(), timeBuffer);
	
	// throw if level is FATAL
	if (lvl == FATAL)
		throw std::runtime_error(buffer.data());
}

void Logger::setLogState(bool state)
{
	_logState = state;
}

void Logger::setLogFileState(bool state)
{
	_logFileState = state;
}

void Logger::setLogDebugState(bool state)
{
	_logDebugState = state;
}

std::string Logger::getLogFileName()
{
	return (Logger::_logFileName);
}