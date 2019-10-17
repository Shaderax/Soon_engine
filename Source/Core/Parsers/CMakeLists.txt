cmake_minimum_required (VERSION 3.10)

set(SRC 
	InitRessourceImporter.cpp
	MeshImporter.cpp
	)

add_library(Parsers ${SRC})

target_link_libraries(Parsers assimp)
