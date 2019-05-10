cmake_minimum_required (VERSION 3.10)

set(SOURCE
	OSGLFW.cpp
	GLFWInput.cpp
	InitGLFW.cpp
	GLFWCallback.cpp
	"../GraphicsInstance.cpp"
	"../GraphicsRenderer.cpp"
	)

add_library(GraphicsGLFW ${SOURCE})

if (${USE_VULKAN})
	add_subdirectory( GLFWVulkan )
	target_link_libraries(GraphicsGLFW GLFWVulkan glfw Input)
else()
	add_subdirectory( GLFWOpenGL )
	target_link_libraries(GraphicsGLFW GLFWOpenGL glfw Input)
endif()
