cmake_minimum_required (VERSION 3.10)

set(SRC 
	OS.cpp
	)

add_library(OS ${SRC})

add_subdirectory(Input)

#target_link_libraries(OS Input)
#target_link_libraries(OS Input Graphics)
