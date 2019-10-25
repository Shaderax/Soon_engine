cmake_minimum_required (VERSION 3.10)

set(SRC 
	Engine.cpp
	./Parsers/InitRessourceImporter.cpp
	./Parsers/MeshImporter.cpp

	./OS/OS.cpp
	
	./OS/Input/Input.cpp

	./Scene/Scene.cpp
	./Scene/Object.cpp

	./Scene/3D/Components/Camera.cpp
	./Scene/3D/Components/ParticlesSystem.cpp
	./Scene/3D/Components/Mesh.cpp

	./Scene/Materials/ShaderMaterial.cpp

	./Renderer/Vulkan/GraphicsInstance.cpp
	./Renderer/Vulkan/GraphicsRenderer.cpp
	./Renderer/Vulkan/PipelineConf.cpp
	)

if(APPLE)
	find_library(
		VULKAN_LIB
		NAMES libvulkan.1.1.101.dylib libvulkan.dylib
		HINTS "${CMAKE_SOURCE_DIR}/ThirdParty/vulkan/libs/macos/"
		NO_DEFAULT_PATH
		)

	find_library(
		MOLTENVK_LIB
		NAMES libMoltenVK.dylib
		HINTS "${CMAKE_SOURCE_DIR}/ThirdParty/MoltenVK/macOS/"
		NO_DEFAULT_PATH
		)
elseif(UNIX)
	find_library(
		VULKAN_LIB
		NAMES libvulkan.so
		HINTS "${CMAKE_SOURCE_DIR}/ThirdParty/vulkan/libs/linux/"
		NO_DEFAULT_PATH
		)
endif()

add_library(Core ${SRC})

add_subdirectory(Renderer)

target_link_libraries(Core ECS GraphicsGLFW ${VULKAN_LIB} assimp)#Parsers)
