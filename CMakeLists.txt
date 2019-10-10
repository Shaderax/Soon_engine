cmake_minimum_required (VERSION 3.10)

#execute_process(COMMAND source export.sh)
set (CMAKE_CXX_STANDARD 20)

set(GLFW_BUILD_EXAMPLES "Build the GLFW example programs" OFF FORCE)
set(GLFW_BUILD_TESTS "Build the GLFW test programs" OFF FORCE)
if (UNIX AND NOT APPLE)
	set(CMAKE_CXX_COMPILER /usr/bin/g++-8)
	execute_process(COMMAND apt-get install libx11-dev)
	execute_process(COMMAND apt-get install xorg-dev libglu1-mesa-dev)
	execute_process(COMMAND apt install libvulkan1 mesa-vulkan-drivers vulkan-utils)
endif()

if (APPLE)
	set(CMAKE_CXX_COMPILER /Users/nrouzeva/.brew/Cellar/gcc/9.2.0_1/bin/g++-9)
endif ()

option (USE_VULKAN "Use Vulkan" ON) 

#set(ENV{VK_ICD_FILENAMES} ${CMAKE_SOURCE_DIR}/ThirdParty/MoltenVK/macOS/MoltenVK_icd.json)
set(ENV{VK_ICD_FILENAMES} "/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/MoltenVK/macOS/MoltenVK_icd.json")
set(ENV{VK_LAYER_PATH} "/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/vulkan/Validation_Layer/explicit_layer.d/macos/")


if(${USE_VULKAN})
	add_definitions(-DUSE_VULKAN)
endif()

include_directories(Source)
include_directories(Modules)
include_directories(ThirdParty/glfw/include/)
include_directories(ThirdParty/assimp_lib/include/)
include_directories(ThirdParty/assimp_lib/code)
include_directories(ThirdParty/)

LINK_DIRECTORIES(
	  ${Assimp_BINARY_DIR}
	    ${Assimp_BINARY_DIR}/code/
		)


project(Soon)

add_compile_options(-Wall -Wextra -g3)

option (ASSIMP_BUILD_TESTS OFF)
option(ASSIMP_NO_EXPORT "" ON)
option (ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT "" OFF)
set(ASSIMP_BUILD_OBJ_IMPORTER ON FORCE)

add_subdirectory(Source)
add_subdirectory(Modules)
add_subdirectory(ThirdParty)
add_subdirectory(Exemples)

add_library (Build INTERFACE)
