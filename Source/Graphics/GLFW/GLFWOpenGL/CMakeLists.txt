cmake_minimum_required (VERSION 3.10)

set(OPENGL_MAJOR_VERSION 4)
set(OPENGL_MINOR_VERSION 1)

set (SRC
	GLFWOpenGLContext.cpp
	GLFWOpenGLHints.cpp
	)

add_library(GLFWOpenGL
	${SRC}
	)

target_link_libraries(GLFWOpenGL glfw)
#// APPLE
target_link_libraries(GLFWOpenGL "-framework AppKit -framework OpenGL -framework IOKit -framework CoreVideo")

configure_file (
	"${CMAKE_CURRENT_SOURCE_DIR}/Config.hpp.in"
	"${CMAKE_CURRENT_SOURCE_DIR}/Config.hpp"
	)
