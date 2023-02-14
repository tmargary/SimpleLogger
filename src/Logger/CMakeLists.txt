add_library(Logger Logger.cpp)
target_compile_options(Logger PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)
target_link_libraries(Logger PUBLIC utils)
target_include_directories(Logger PUBLIC include)
