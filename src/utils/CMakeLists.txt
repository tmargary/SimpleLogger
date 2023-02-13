add_library(utils utils.cpp)
target_include_directories(utils PUBLIC include)

find_package(nlohmann_json CONFIG REQUIRED)

target_link_libraries(utils PRIVATE nlohmann_json)