cmake_minimum_required (VERSION 3.10)

set(SRC 
	./Components/ParticlesSystem.cpp
	./Components/Mesh.cpp
	)

add_library(3D ${SRC})
