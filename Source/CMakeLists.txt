cmake_minimum_required (VERSION 3.10)

add_compile_options(-Wall -Wextra -g3)

add_subdirectory(Core)

add_library(Soon)

target_link_libraries(Soon Core ECS)
