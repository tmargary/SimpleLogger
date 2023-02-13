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

class Logger {
 public:
  Logger(const std::string &filePath, LogLevel level);

  void log(LogLevel messageLevel, const std::string &message);

  ~Logger();

 private:
  std::ofstream logFile;
  std::string filePath;
  LogLevel level;
};

#endif
