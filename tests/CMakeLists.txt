find_package(GTest REQUIRED)

add_executable(LoggerTest LoggerTest.cpp)

target_link_libraries(LoggerTest
 PRIVATE
  GTest::GTest
  Logger)

add_test(LoggerGTest LoggerTest)

