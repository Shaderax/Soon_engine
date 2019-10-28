cmake_minimum_required (VERSION 3.10)
set(CMAKE_CXX_COMPILER g++)
set (CMAKE_CXX_STANDARD 17)

#set(GLFW_BUILD_EXAMPLES "Build the GLFW example programs" OFF FORCE)
#set(GLFW_BUILD_TESTS "Build the GLFW test programs" OFF FORCE)

if (UNIX AND NOT APPLE)
	set(CMAKE_CXX_COMPILER g++)
	execute_process(COMMAND apt-get install libx11-dev)
	execute_process(COMMAND apt-get install xorg-dev libglu1-mesa-dev)
	execute_process(COMMAND apt install libvulkan1 mesa-vulkan-drivers vulkan-utils)
endif()

find_package(assimp)

if (APPLE)
	if (assimp_FOUND)
		message("assimp FOUND")
	else()
		execute_process(COMMAND brew install assimp)
	endif()
elseif (UNIX)
	if (glfw3_FOUND)
		message("assimp FOUND")
	else()
		execute_process(COMMAND sudo apt-get install libassimp-dev)
	endif()
endif()

#message( ${CMAKE_CURRENT_SOURCE_DIR} )

#set(ENV{VK_ICD_FILENAMES} "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/MoltenVK/macOS/MoltenVK_icd.json")
#set(ENV{VK_LAYER_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/vulkan/Validation_Layer/explicit_layer.d/macos/")

include_directories(Source)
include_directories(Modules)
#include_directories(ThirdParty/glfw/include/)
include_directories(/usr/include/)
#include_directories(ThirdParty/assimp_lib/include/)
#include_directories(ThirdParty/assimp_lib/code)
include_directories(ThirdParty/)

project(Soon)

#option (ASSIMP_BUILD_TESTS OFF)
#option(ASSIMP_NO_EXPORT "" ON)
#option (ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT "" OFF)
#set(ASSIMP_BUILD_OBJ_IMPORTER ON FORCE)

add_subdirectory(ThirdParty)
add_subdirectory(Modules)
add_subdirectory(Source)
add_subdirectory(Exemples)
