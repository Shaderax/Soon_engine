cmake_minimum_required (VERSION 3.10)

set (CMAKE_CXX_STANDARD 11)

project(Soon)

add_subdirectory(Modules)

add_subdirectory(ThirdParty)

add_library (Soon INTERFACE)
