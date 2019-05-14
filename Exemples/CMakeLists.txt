cmake_minimum_required (VERSION 3.10)

set (CMAKE_CXX_STANDARD 11)

project(Test)

add_executable (Test main_test.cpp)

target_link_libraries(Test Core ECS Graphics glfw Scene)
