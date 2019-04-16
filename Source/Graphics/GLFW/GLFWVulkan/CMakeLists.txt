cmake_minimum_required (VERSION 3.10)

set (SRC
	GLFWVulkan.cpp
	GLFWVulkanHints.cpp
	)

add_library(GLFWVulkan
	${SRC}
	)

find_library(
		VULKAN_LIB
		NAMES libvulkan.dylib
		HINTS "/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/vulkan/libs/macos/"
		NO_DEFAULT_PATH
	)

target_compile_definitions(GLFWVulkan PUBLIC USE_VULKAN)
#link_directories("/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/vulkan/libs")
target_link_libraries(GLFWVulkan glfw ${VULKAN_LIB})
#// APPLE
#target_link_libraries(GLFWVulkan "-framework AppKit -framework OpenGL -framework IOKit -framework CoreVideo")
