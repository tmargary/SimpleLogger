cmake_minimum_required(VERSION 3.16)
project(SimpleLogger LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_COMPILER /usr/bin/g++)

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)
