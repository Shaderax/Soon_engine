cmake_minimum_required (VERSION 3.10)

option (USE_VULKAN "Use Vulkan" OFF) 

include_directories(Source)
include_directories(Modules)
include_directories(ThirdParty/glfw/include/)

set (CMAKE_CXX_STANDARD 11)

project(Soon)

add_subdirectory(Source)
add_subdirectory(Modules)
add_subdirectory(ThirdParty)

add_subdirectory(Exemples)

add_library (Build INTERFACE)
