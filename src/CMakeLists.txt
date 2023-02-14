add_subdirectory(Logger)
add_subdirectory(utils)
add_executable(main main.cpp)
target_compile_options(main PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)
find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(main PRIVATE utils Logger nlohmann_json)