#include <gtest/gtest.h>
#include <Logger/Logger.h>
#include <utils/utils.h>
#include <cstring>
#include <fstream>
#include <array>
#include <iostream>

// Test that the constructor creates a log file with the correct path and extension
TEST(LoggerTest, CorrectPathAndExtension)
{
    std::string path = get_cwd();
    std::string freq = "day";
    LogLevel level = LogLevel::INFO;
    Logger logger(path, freq, level);

    std::string expectedFilePath = path + "/log_" + DateTimeNow("%Y_%m_%d") + ".txt";
    EXPECT_EQ(logger.get_filePath(), expectedFilePath);
}

// Test that the constructor throws an exception for an unexpected frequency
TEST(LoggerTest, ThrowsExceptionForUnexpectedFrequency)
{
    std::string path = get_cwd();
    std::string freq = "unexpected";
    LogLevel level = LogLevel::INFO;

    EXPECT_THROW(Logger logger(path, freq, level), std::runtime_error);
}

// Test that the constructor sets the log level correctly
TEST(LoggerTest, LogLevelIsSet)
{
    std::string path = get_cwd();
    std::string freq = "day";
    LogLevel level = LogLevel::ERROR;
    Logger logger(path, freq, level);

    EXPECT_EQ(logger.get_level(), level);
}

TEST(LoggerTest, TestConstructor)
{
    // Testing Logger Constructor
    std::string path = get_cwd();
    std::string freq = "day";
    LogLevel level = LogLevel::INFO;
    Logger logger(path, freq, level);

    std::string name = "/log_", ext = ".txt";
    std::string filePath = path + name + DateTimeNow("%Y_%m_%d") + ext;

    std::ifstream file(filePath);
    EXPECT_TRUE(file.good());
    file.close();
}

TEST(LoggerTest, TestLogLevels)
{
    // Lowest level: DEBUG; In a loop we add different messages and expect the last line to contain that message.
    std::string path = get_cwd();
    std::string freq = "day";
    LogLevel level = LogLevel::DEBUG;
    Logger logger(path, freq, level);

    std::string name = "/log_", ext = ".txt";
    std::string filePath = path + name + DateTimeNow("%Y_%m_%d") + ext;

    std::ifstream file(filePath);
    std::string lastLine, line;

    std::array<LogLevel, 4> logLevels = {DEBUG, INFO, WARNING, ERROR};
    std::map<LogLevel, std::string> logLevelToString{
        {DEBUG, "DEBUG"},
        {INFO, "INFO"},
        {WARNING, "WARNING"},
        {ERROR, "ERROR"},
    };

    for (const auto &logLevel : logLevels)
    {
        std::string message = logLevelToString[logLevel] + " message";
        logger.log(logLevel, message);

        while (std::getline(file, line))
        {
            lastLine = line;
        }

        EXPECT_TRUE(lastLine.find("[" + logLevelToString[logLevel] + "]") != std::string::npos);
        EXPECT_TRUE(lastLine.find(message) != std::string::npos);
        file.clear();
        file.seekg(0, file.beg);
    }
    file.close();
}

TEST(LoggerTest, TestLogLevel)
{
    // Lowest level: WARNING; Then we try to log a DEBUG message which shouldn't make it to the log file. So we expect false.
    std::string path = get_cwd();
    std::string freq = "day";
    LogLevel level = LogLevel::WARNING;
    Logger logger(path, freq, level);

    logger.log(DEBUG, "debug message");
    std::ifstream file("test.log");

    std::string lastLine, line;
    while (std::getline(file, line))
    {
        lastLine = line;
    }

    std::getline(file, lastLine);

    EXPECT_FALSE(std::getline(file, lastLine));
    file.close();
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
