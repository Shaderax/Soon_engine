cmake_minimum_required (VERSION 3.10)

set(SRC 
	Scene.cpp
	Object.cpp
	)

add_library(Scene ${SRC})
add_subdirectory(3D)
#target_link_libraries(Scene ECS Graphics assimp)
target_link_libraries(Scene Input 3D Materials)
