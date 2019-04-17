cmake_minimum_required (VERSION 3.10)

set (SRC
	GLFWVulkan.cpp
	GLFWVulkanHints.cpp
	)

add_library(GLFWVulkan
	${SRC}
	)


if(APPLE)
message(${CMAKE_SOURCE_DIR})
find_library(
		VULKAN_LIB
		NAMES libvulkan.dylib
		HINTS "${CMAKE_SOURCE_DIR}/ThirdParty/vulkan/libs/macos/"
		NO_DEFAULT_PATH
	)
elseif(UNIX)
message(${CMAKE_SOURCE_DIR})
find_library(
		VULKAN_LIB
		NAMES libvulkan.so
		HINTS "${CMAKE_SOURCE_DIR}/ThirdParty/vulkan/libs/linux/"
		NO_DEFAULT_PATH
	)

endif()

target_compile_definitions(GLFWVulkan PUBLIC USE_VULKAN)
#link_directories("/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/vulkan/libs")
target_link_libraries(GLFWVulkan glfw ${VULKAN_LIB})
#// APPLE
#target_link_libraries(GLFWVulkan "-framework AppKit -framework OpenGL -framework IOKit -framework CoreVideo")
