#ifndef LOGGER_H
#define LOGGER_H

#include <map>
#include <string>
#include <fstream>

enum LogLevel
{
  DEBUG,
  INFO,
  WARNING,
  ERROR,
};

std::map<LogLevel, std::string> logLevelToString{
    {DEBUG, "DEBUG"},
    {INFO, "INFO"},
    {WARNING, "WARNING"},
    {ERROR, "ERROR"},
};

class Logger {
 public:
  Logger(const std::string &filePath, LogLevel level) : filePath(filePath), level(level) {
    logFile.open(filePath, std::ios::out | std::ios::app);
  }

  ~Logger() {
    logFile.close();
  }

  void log(LogLevel messageLevel, const std::string &message) {
    if (messageLevel >= level) {
      logFile << logLevelToString[messageLevel] << ": " << message << std::endl;
    }
  }

 private:
  std::ofstream logFile;
  std::string filePath;
  LogLevel level;
};

#endif
