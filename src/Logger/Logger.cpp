#include <Logger/Logger.h>
#include <utils/utils.h>
#include <iostream>

std::map<LogLevel, std::string> const logLevelToString{
    {DEBUG, "DEBUG"},
    {INFO, "INFO"},
    {WARNING, "WARNING"},
    {ERROR, "ERROR"},
};

Logger::Logger(const std::string &path, const std::string &freq, LogLevel level) : path(path), freq(freq), level(level)
{   

    std::string name = "/log_", ext = ".txt";

    if (freq == "second")
    {
        filePath = path + name + DateTimeNow("%Y_%m_%d_%X") + ext;
    }
    else if (freq == "minute")
    {
        filePath = path + name + DateTimeNow("%Y_%m_%d_%H_%M") + ext;
    }
    else if (freq == "hour")
    {
        filePath = path + name + DateTimeNow("%Y_%m_%d_%H") + ext;
    }
    else if (freq == "day")
    {
        filePath = path + name + DateTimeNow("%Y_%m_%d") + ext;
    }
    else if (freq == "week")
    {
        filePath = path + name + DateTimeNow("%Y_%U") + ext;
    }
    else if (freq == "month")
    {
        filePath = path + name + DateTimeNow("%Y_%m") + ext;
    }
    else if (freq == "quarter")
    {
        filePath = path + name + DateTimeNow("%Y_Q%q") + ext;
    }
    else if (freq == "year")
    {
        filePath = path + name + DateTimeNow("%Y") + ext;
    }
    else
    {
        throw std::runtime_error("Error: Unexpected frequency specified: " + freq);
    }

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
                    << "[" << logLevelToString.at(messageLevel) << "]"
                    << ": " << message << std::endl;
        }
        catch (const std::ios_base::failure &e)
        {
            std::cerr << "Error opening or writing to log file: " << e.what() << std::endl;
        }
    }
}
