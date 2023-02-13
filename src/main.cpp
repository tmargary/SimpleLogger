#include <iostream>
#include <limits.h>
#include <libgen.h>
#include <unistd.h>
#include <filesystem>
#include <nlohmann/json.hpp>
namespace fs = std::filesystem;

#include <Logger/Logger.h>

std::string get_cwd()
{
  char path[PATH_MAX];
  strncpy(path, __FILE__, sizeof(path));
  char *dir = dirname(path);
  return dir;
}

int main()
{

  std::string cwd = get_cwd();

  LogLevel level;
  nlohmann::json config = nlohmann::json::parse(std::ifstream(cwd + "/config.json"));
  if (config.count("log_level"))
  {
    std::string logLevelString = config["log_level"];
    if (logLevelString == "DEBUG")
    {
      level = DEBUG;
    }
    else if (logLevelString == "INFO")
    {
      level = INFO;
    }
    else if (logLevelString == "WARNING")
    {
      level = WARNING;
    }
    else if (logLevelString == "ERROR")
    {
      level = ERROR;
    }
    else
    {
      throw("abc");
    }
  }
  Logger logger(cwd + "/log.txt", level);
  logger.log(DEBUG, "Debug message");
  logger.log(INFO, "Info message");
  logger.log(WARNING, "Warning message");
  logger.log(ERROR, "Error message");
  return 0;
}
