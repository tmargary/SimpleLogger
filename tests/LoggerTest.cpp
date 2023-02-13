#include <Logger/Logger.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <gtest/gtest.h>

TEST(LoggerTest, TestConstructor) {
    // Testing Logger Constructor
    Logger logger("test.log", INFO);
    std::ifstream file("test.log");
    EXPECT_TRUE(file.good());
    file.close();
}

TEST(LoggerTest, TestLogLevels) {
    // Lowest level: DEBUG; In a loop we add different messages and expect the last line to contain that message.
    Logger logger("test.log", DEBUG);
    std::ifstream file("test.log");
    std::string lastLine, line;

    LogLevel logLevels[] = {DEBUG, INFO, WARNING, ERROR};
    std::map<LogLevel, std::string> logLevelToString{
    {DEBUG, "DEBUG"},
    {INFO, "INFO"},
    {WARNING, "WARNING"},
    {ERROR, "ERROR"},
};

    for (const auto& logLevel : logLevels) {
        std::string message = logLevelToString[logLevel] + " message";
        logger.log(logLevel, message);

        while (std::getline(file, line)) {
            lastLine = line;
        }

        EXPECT_TRUE(lastLine.find("[" + logLevelToString[logLevel] + "]") != std::string::npos);
        EXPECT_TRUE(lastLine.find(message) != std::string::npos);
        file.clear();
        file.seekg(0, file.beg);
    }
    file.close();
}

TEST(LoggerTest, TestLogLevel) {
    // Lowest level: WARNING; Then we try to log a DEBUG message which shouldn't make it to the log file. So we expect false.
    Logger logger("test.log", WARNING);
    logger.log(DEBUG, "debug message");
    std::ifstream file("test.log");

    std::string lastLine, line;
    while (std::getline(file, line)) {
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
