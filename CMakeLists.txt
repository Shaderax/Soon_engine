cmake_minimum_required (VERSION 3.10)

option (USE_VULKAN "Use Vulkan" OFF) 

#set(ENV{VK_ICD_FILENAMES} ${CMAKE_SOURCE_DIR}/ThirdParty/MoltenVK/macOS/MoltenVK_icd.json)

if(${USE_VULKAN})
	add_definitions(-DUSE_VULKAN)
endif()

include_directories(Source)
include_directories(Modules)
include_directories(ThirdParty/glfw/include/)
include_directories(ThirdParty/)

set (CMAKE_CXX_STANDARD 11)

project(Soon)

add_subdirectory(Source)
add_subdirectory(Modules)
add_subdirectory(ThirdParty)

add_subdirectory(Exemples)

add_library (Build INTERFACE)
