#include <Logger/Logger.h>
#include <utils.h>

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
        logFile << "[" << DateTimeNow() << "]" << "[" << logLevelToString[messageLevel] << "]" << ": " << message << std::endl;
    } 
}
