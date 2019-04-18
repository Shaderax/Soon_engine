cmake_minimum_required (VERSION 3.10)

set (SRC
	GLFWVulkan.cpp
	GLFWVulkanHints.cpp
	)

add_library(GLFWVulkan
	${SRC}
	)

if(APPLE)
#	find_library(
#			VULKAN_LIB
#			NAMES libvulkan.dylib
#			HINTS "${CMAKE_SOURCE_DIR}/ThirdParty/vulkan/libs/macos/"
#			NO_DEFAULT_PATH
#		)

	find_library(
			MOLTENVK_LIB
			NAMES libMoltenVK.dylib
			HINTS "${CMAKE_SOURCE_DIR}/ThirdParty/MoltenVK/macOS/"
			NO_DEFAULT_PATH
		)

target_link_libraries(GLFWVulkan glfw ${MOLTENVK_LIB})
#set(PRIVATE_COMPILE_DEFINITIONS VK_USE_PLATFORM_MACOS_MVK=1)
#include_directories("${CMAKE_SOURCE_DIR}/ThirdParty/MoltenVK/include")

elseif(UNIX)
	find_library(
			VULKAN_LIB
			NAMES libvulkan.so
			HINTS "${CMAKE_SOURCE_DIR}/ThirdParty/vulkan/libs/linux/"
			NO_DEFAULT_PATH
		)
	target_link_libraries(GLFWVulkan glfw ${VULKAN_LIB})

endif()

#target_compile_definitions(GLFWVulkan PUBLIC USE_VULKAN=1)
#link_directories("/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/vulkan/libs")
#target_link_libraries(GLFWVulkan glfw ${VULKAN_LIB} ${MOLTENVK_LIB})
#// APPLE
#target_link_libraries(GLFWVulkan "-framework AppKit -framework OpenGL -framework IOKit -framework CoreVideo")
