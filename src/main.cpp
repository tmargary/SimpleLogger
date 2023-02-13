#include <iostream>
#include <limits.h>
#include <nlohmann/json.hpp>
#include <filesystem>

#ifdef _WIN32
#include <windows.h>
#define getcwd _getcwd
#else
#include <unistd.h>
#include <libgen.h>
#endif

namespace fs = std::filesystem;

#include <Logger/Logger.h>
#include <utils/utils.h>


std::string get_cwd()
{
  char path[PATH_MAX];
#ifdef _WIN32
  char drive[MAX_PATH];
  char dir[MAX_PATH];
  char filename[MAX_PATH];
  char extension[MAX_PATH];

  GetModuleFileName(NULL, path, MAX_PATH);
  _splitpath_s(path, drive, MAX_PATH, dir, MAX_PATH, filename, MAX_PATH, extension, MAX_PATH);

  return std::string(drive) + std::string(dir);
#else
  strncpy(path, __FILE__, sizeof(path));
  char *dir = dirname(path);
  return dir;
#endif
}

LogLevel get_level(const std::string &config_path)
{
  LogLevel level;
  nlohmann::json config = nlohmann::json::parse(std::ifstream(config_path));
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
      level = DEBUG;
    }
  }
  return level;
}

int main()
{

  std::string cwd = get_cwd();
  std::string config_path = cwd + "/config.json";
  LogLevel level = get_level(config_path);

  Logger logger(cwd + "/log_" + DateTimeNow("%Y_%m_%d") + ".txt", level);
  logger.log(DEBUG, "Debug message");
  logger.log(INFO, "Info message");
  logger.log(WARNING, "Warning message");
  logger.log(ERROR, "Error message");
  return 0;
}