find_package(GTest REQUIRED)

add_executable(LoggerTest LoggerTest.cpp)
target_compile_options(LoggerTest PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

target_link_libraries(LoggerTest
 PRIVATE
  GTest::GTest
  Logger)

add_test(LoggerGTest LoggerTest)

