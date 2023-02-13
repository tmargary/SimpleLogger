#include <Logger/Logger.h>
#include <utils/utils.h>
#include <iostream>

std::map<LogLevel, std::string> logLevelToString{
    {DEBUG, "DEBUG"},
    {INFO, "INFO"},
    {WARNING, "WARNING"},
    {ERROR, "ERROR"},
};

Logger::Logger(const std::string &filePath, LogLevel level) : filePath(filePath), level(level)
{
    logFile.open(filePath, std::ios::out | std::ios::app);
}

Logger::~Logger()
{
    logFile.close();
}

void Logger::log(LogLevel messageLevel, const std::string &message)
{
    if (messageLevel >= level)
    {
        try
        {
            logFile << "[" << DateTimeNow() << "]"
                    << "[" << logLevelToString[messageLevel] << "]"
                    << ": " << message << std::endl;
        }
        catch (const std::ios_base::failure &e)
        {
            std::cerr << "Error opening or writing to log file: " << e.what() << std::endl;
        }
    }
}
