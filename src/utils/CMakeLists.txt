add_library(utils utils.cpp)
target_compile_options(utils PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)
target_include_directories(utils PUBLIC include)

find_package(nlohmann_json CONFIG REQUIRED)

target_link_libraries(utils PRIVATE nlohmann_json)