#ifndef LOGGER_H
#define LOGGER_H

#include <map>
#include <string>
#include <fstream>

enum LogLevel
{
  DEBUG = 0,
  INFO = 1,
  WARNING = 2,
  ERROR = 3,
};

class Logger
{
public:
  Logger(const std::string &path, const std::string &freq, LogLevel level);
  void log(LogLevel messageLevel, const std::string &message);
  std::string get_freq(){return freq;}
  std::string get_path(){return path;}
  std::string get_filePath(){return filePath;}
  LogLevel get_level(){return level;}
  ~Logger();

private:
  std::string freq; 
  std::ofstream logFile;
  std::string path;
  std::string filePath;
  LogLevel level;
};

#endif
