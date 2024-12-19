#include "Logger.h"

int main()
{
    // Test setting log states
    Logger::setLogState(true);
    Logger::setLogFileState(false);
    Logger::setLogDebugState(true);

    // Test logging various levels
    // Logger::log(FATAL, "This is a fatal message.");
    Logger::log(ERROR, "This is an error message.");
    Logger::log(WARNING, "This is a warning message.");
    Logger::log(INFO, "This is an info message.");
    Logger::log(TRACE, "This is a trace message.");
    Logger::log(DEBUG, "This is a debug message.");

    // Enable file logging
    Logger::setLogFileState(true);
    Logger::log(INFO, "This message should also be written to the log file: %s", Logger::getLogFileName().c_str());

    // Display the log file name
    std::cout << "Log file name: " << Logger::getLogFileName() << std::endl;

    // Test logging with formatting
    Logger::log(DEBUG, "Formatted log: Value=%d, String=%s", 42, "Test");

    return 0;
}