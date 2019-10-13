cmake_minimum_required (VERSION 3.10)

add_compile_options(-Wall -Wextra -g3)

add_subdirectory(Core)
add_subdirectory(Graphics)
add_subdirectory(Scene)
#add_subdirectory(Utilities)

add_library(Soon INTERFACE)
