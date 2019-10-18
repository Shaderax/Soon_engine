cmake_minimum_required (VERSION 3.10)

set (SRC
	GraphicsInstance.cpp
	GraphicsRenderer.cpp
	GraphicsPipelineConf.cpp
	)

add_library(GraphicsVulkan
	${SRC}
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

target_link_libraries(GraphicsVulkan glfw ${VULKAN_LIB})
#link_directories("${CMAKE_SOURCE_DIR}/ThirdParty/vulkan/libs/macos/")
#set(PRIVATE_COMPILE_DEFINITIONS VK_USE_PLATFORM_MACOS_MVK=1)
#include_directories("${CMAKE_SOURCE_DIR}/ThirdParty/MoltenVK/include")

elseif(UNIX)
	find_library(
			VULKAN_LIB
			NAMES libvulkan.so
			HINTS "${CMAKE_SOURCE_DIR}/ThirdParty/vulkan/libs/linux/"
			NO_DEFAULT_PATH
		)
	target_link_libraries(GraphicsVulkan glfw ${VULKAN_LIB})

endif()

#link_directories("/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/vulkan/libs/macos")
#target_link_libraries(GraphicsVulkan glfw ${VULKAN_LIB} ${MOLTENVK_LIB})
#// APPLE
#target_link_libraries(GraphicsVulkan "-framework AppKit -framework OpenGL -framework IOKit -framework CoreVideo")

#42 Mac :
#VK_ICD_FILENAMES=/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/MoltenVK/macOS/MoltenVK_icd.json
#LD_LIBRARY_PATH=:/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/vulkan/libs/macos
#VK_LAYER_PATH=/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/vulkan/Validation_Layer/explicit_layer.d/macos/

#linux :
#VK_LAYER_PATH=/home/shaderax/Documents/Project/Soon_engine/ThirdParty/vulkan/Validation_Layer/explicit_layer.d/linux/
