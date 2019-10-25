cmake_minimum_required (VERSION 3.10)

#list(APPEND CMAKE_MODULE_PATH "~/.brew/lib/cmake/glfw3")
find_package(glfw3)

if (APPLE)
	if (glfw3_FOUND)
		message("GLFW3 FOUND")
		include_directories("/usr/local/include/")
	else()
		execute_process(COMMAND brew install glfw3)
	endif()
elseif (UNIX)
	if (glfw3_FOUND)
		message("GLFW3 FOUND")
		include_directories("/usr/include/")
	else()
		execute_process(COMMAND sudo apt-get install libglfw3)
	endif()
endif()

set(SOURCE
	Init.cpp
	Hints.cpp
	Callback.cpp
	)

add_library(GraphicsGLFW ${SOURCE} ${GLFW3_LIBRARIES})
target_link_libraries(GraphicsGLFW glfw)
