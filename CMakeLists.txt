cmake_minimum_required (VERSION 3.14)

project(Soon)

add_library (Soon INTERFACE)

add_subdirectory(Modules)

add_subdirectory(ThirdParty/glfw)
