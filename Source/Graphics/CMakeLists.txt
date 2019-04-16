cmake_minimum_required (VERSION 3.10)

add_subdirectory(GLFW)

add_library(Graphics "GraphicsInstance.cpp")

target_link_libraries(Graphics GraphicsGLFW)
