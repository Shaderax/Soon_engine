cmake_minimum_required (VERSION 3.10)

set(SRC 
	Engine.cpp
	)

add_library(Core ${SRC})

add_subdirectory(OS)
add_subdirectory(Parsers)

#target_link_libraries(Core OS)
target_link_libraries(Core OS Parsers)
