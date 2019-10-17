cmake_minimum_required (VERSION 3.10)

set(SRC 
	Engine.cpp
	)

add_library(Core ${SRC})
target_link_libraries(Core OS)

add_subdirectory(OS)
add_subdirectory(Parsers)

target_link_libraries(Core GraphicsVulkan Parsers)
