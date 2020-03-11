cmake_minimum_required(VERSION 3.10)

set(SRC ./Sources/spvReader.cpp
	./ThirdParty/SPIRV-Cross/spirv_cross_c.cpp
	./ThirdParty/SPIRV-Cross/spirv_cross_util.cpp
	./ThirdParty/SPIRV-Cross/spirv_msl.cpp
	./ThirdParty/SPIRV-Cross/spirv_cfg.cpp
	./ThirdParty/SPIRV-Cross/spirv_cross.cpp
	./ThirdParty/SPIRV-Cross/spirv_glsl.cpp
	./ThirdParty/SPIRV-Cross/spirv_parser.cpp
	./ThirdParty/SPIRV-Cross/spirv_cpp.cpp
	./ThirdParty/SPIRV-Cross/spirv_cross_parsed_ir.cpp
	./ThirdParty/SPIRV-Cross/spirv_hlsl.cpp
	./ThirdParty/SPIRV-Cross/spirv_reflect.cpp)

include_directories(./ThirdParty/SPIRV-Cross/)

add_library(SpirvReader STATIC ${SRC})

add_executable(testee  ./Sources/main.cpp ${SRC})
