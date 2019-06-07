cmake_minimum_required (VERSION 3.10)

execute_process(COMMAND source export.sh)

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
include_directories(ThirdParty/)

set (CMAKE_CXX_STANDARD 11)

project(Soon)

add_subdirectory(Source)
add_subdirectory(Modules)
add_subdirectory(ThirdParty)

add_subdirectory(Exemples)

add_library (Build INTERFACE)
