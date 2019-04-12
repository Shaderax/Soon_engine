cmake_minimum_required (VERSION 3.10)

set(SOURCE
	OSGLFW.cpp
	GLFWInput.cpp
	InitGLFW.cpp
	GLFWCallback.cpp
	)

add_library(GraphicsGLFW ${SOURCE})

add_subdirectory( GLFWOpenGL )

target_link_libraries(GraphicsGLFW GLFWOpenGL glfw)

#find_package(OpenGL REQUIRED)
