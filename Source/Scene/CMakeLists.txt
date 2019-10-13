cmake_minimum_required (VERSION 3.10)

set(SRC 
	Scene.cpp
	Object.cpp
	./3D/Components/Mesh.cpp
	./3D/Components/ParticlesSystem.cpp
	./Common/ShaderMaterial.cpp
	)

add_library(Scene ${SRC})
target_link_libraries(Scene Graphics assimp)
