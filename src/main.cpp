#include <thread>
#include <nlohmann/json.hpp>

#include <Logger/Logger.h>
#include <utils/utils.h>


LogLevel get_config_level(const std::string &config_path)
{
  LogLevel level = DEBUG;
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
  }
  return level;
}

/*
int main()
{
  std::string freq = "day";
  std::string path = getCwd();
  std::string config_path = path + "/config.json";
  LogLevel level = get_config_level(config_path);

  Logger logger(path, freq, level);
  logger.log(DEBUG, "Debug message");
  logger.log(INFO, "Info message");
  logger.log(WARNING, "Warning message");
  logger.log(ERROR, "Error message");
  return 0;
}
*/

int main() {
    std::string freq = "day";
    std::string path = getCwd();
    std::string config_path = path + "/config.json";
    LogLevel level = get_config_level(config_path);

    Logger logger(path, freq, level);
    std::vector<std::thread> threads;

    const int loop_cnt = 10;
    const int level_cnt = 4;
    for (int i = 0; i < loop_cnt; i++) 
    {
        threads.emplace_back([&logger, i] {
            std::string message = "Thread " + std::to_string(i) + " error message";
            logger.log(static_cast<LogLevel>(i % level_cnt), message);
        });
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}