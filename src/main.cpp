#include <nlohmann/json.hpp>

#include <Logger/Logger.h>
#include <utils/utils.h>


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
  std::string freq = "day";
  std::string path = get_cwd();
  std::string config_path = path + "/config.json";
  LogLevel level = get_level(config_path);

  Logger logger(path, freq, level);
  logger.log(DEBUG, "Debug message");
  logger.log(INFO, "Info message");
  logger.log(WARNING, "Warning message");
  logger.log(ERROR, "Error message");
  return 0;
}