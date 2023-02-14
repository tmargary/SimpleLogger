cmake_minimum_required(VERSION 3.16)
project(SimpleLogger LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

# Add the source files directory
add_subdirectory(src)
# Add the test files directory
add_subdirectory(tests)