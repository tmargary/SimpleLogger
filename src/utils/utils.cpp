#include <iostream>
#include <chrono>
#include <ctime>
#include <sstream>

std::string DateTimeNow(const char *format = "%Y-%m-%d %X")
{
  auto now = std::chrono::system_clock::now();
  auto in_time_t = std::chrono::system_clock::to_time_t(now);
  std::tm tm = *std::localtime(&in_time_t);

  std::stringstream ss;
  char buffer[80];
  strftime(buffer, 80, format, &tm);
  ss << buffer;
  return ss.str();
}
