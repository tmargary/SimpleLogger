add_library(Logger Logger.cpp)
target_link_libraries(Logger PUBLIC utils)
target_include_directories(Logger PUBLIC include)
