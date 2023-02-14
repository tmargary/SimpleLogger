#include <iostream>
#include <chrono>
#include <ctime>
#include <sstream>
#include <filesystem>

std::string DateTimeNow(const char *format = "%Y-%m-%d %X")
{
  auto now = std::chrono::system_clock::now();
  auto in_time_t = std::chrono::system_clock::to_time_t(now);
  std::tm tm;
  localtime_r(&in_time_t, &tm);

  std::stringstream ss;
  char buffer[80];
  strftime(buffer, 80, format, &tm);
  ss << buffer;
  return ss.str();
}

std::string get_cwd()
{
    std::filesystem::path current_path = std::filesystem::current_path();
    while (!std::filesystem::exists(current_path / "CMakeLists.txt")) {
        current_path = current_path.parent_path();
        if (current_path.empty()) {
            throw std::runtime_error("Error: could not find project root directory");
        }
    }
    return current_path.string();
}