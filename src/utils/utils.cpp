#include <iostream>
#include <array>
#include <chrono>
#include <ctime>
#include <sstream>
#include <filesystem>

std::string dateTimeNow(const char *format = "%Y-%m-%d %X")
{
    const int kBufferSize = 80;
    auto now = std::chrono::system_clock::now();
    auto inTimeT = std::chrono::system_clock::to_time_t(now);
    std::tm tm {};

#ifdef _WIN32
    localtime_s(&tm, &inTimeT);
#else
    localtime_r(&inTimeT, &tm);
#endif
    std::stringstream ss;
    std::array<char, kBufferSize> buffer{};
    strftime(buffer.data(), kBufferSize, format, &tm);
    ss << buffer.data();
    return ss.str();
}

std::string getCwd()
{
    std::filesystem::path current_path = std::filesystem::current_path();
    while (!std::filesystem::exists(current_path / "CMakeLists.txt"))
    {
        current_path = current_path.parent_path();
        if (current_path.empty())
        {
            throw std::runtime_error("Error: could not find project root directory");
        }
    }
    return current_path.string();
}