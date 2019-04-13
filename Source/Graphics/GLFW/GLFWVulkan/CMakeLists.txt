cmake_minimum_required (VERSION 3.10)

set (SRC
	GLFWVulkanContext.cpp
	GLFWVulkanHints.cpp
	)

add_library(GLFWVulkan
	${SRC}
	)

target_link_libraries(GLFWVulkan glfw)
#// APPLE
target_link_libraries(GLFWVulkan "-framework AppKit -framework OpenGL -framework IOKit -framework CoreVideo")
