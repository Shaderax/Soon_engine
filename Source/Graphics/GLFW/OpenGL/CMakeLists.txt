cmake_minimum_required (VERSION 3.10)

set(OPENGL_MAJOR_VERSION 4)
set(OPENGL_MINOR_VERSION 1)

add_library(OpenGL
	GLFWOpenGLContext.cpp
	GLFWOpenGLHints.cpp
	)

configure_file (
	"${CMAKE_CURRENT_SOURCE_DIR}/Config.hpp.in"
	"${CMAKE_CURRENT_SOURCE_DIR}/Config.hpp"
	)
