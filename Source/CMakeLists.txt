cmake_minimum_required (VERSION 3.10)

add_subdirectory(Core)
add_subdirectory(Graphics)
add_subdirectory(Scene)
#add_subdirectory(Utilities)

add_library(Source INTERFACE
	)

target_link_libraries(Source INTERFACE Core)
