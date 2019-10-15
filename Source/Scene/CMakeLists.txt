cmake_minimum_required (VERSION 3.10)

set(SRC 
	Scene.cpp
	Object.cpp
	./3D/Components/Mesh.cpp
	./3D/Components/ParticlesSystem.cpp
	)

add_library(Scene ${SRC})
#target_link_libraries(Scene ECS Graphics assimp)
