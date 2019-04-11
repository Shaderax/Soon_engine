cmake_minimum_required (VERSION 3.10)

set(SOURCE
	OSGLFW.cpp
	GLFWInput.cpp
	InitGLFW.cpp
	)

add_library(GLFW ${SOURCE})

add_subdirectory(OpenGL)

target_link_libraries(GLFW OpenGL)
