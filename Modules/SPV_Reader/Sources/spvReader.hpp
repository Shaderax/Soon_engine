#include <spirv_glsl.hpp>
#include <fstream>
#include <vector>
#include <iostream>

static std::vector<std::uint32_t> ReadFile(const std::string& filename);

namespace SpirvReader
{
	struct Member
	{
		std::string	name;
		uint32_t	size;
		uint32_t	offset;
		spirv_cross::SPIRType _type;
	};

	struct Block
	{
		std::string	name;
		uint32_t	size;
		uint32_t	set;
		uint32_t	binding;
		std::vector<Member> members;
		bool isTexture;
		spirv_cross::SPIRType _type;
	};

	struct IOData
	{
		std::string	name;
		spirv_cross::SPIRType type;
		uint32_t	location;
	};

	struct ShaderData
	{
		std::vector<IOData> input;
		//std::vector<IOData> output;
		std::vector<Block> data;
	};

	void GetTexturesUniformsResources( spirv_cross::CompilerGLSL& gl, spirv_cross::SmallVector<spirv_cross::Resource>& res, std::vector<Block>& blocks);

	void GetUniformsResources( spirv_cross::CompilerGLSL& gl, spirv_cross::SmallVector<spirv_cross::Resource>& res, std::vector<Block>& blocks);

	void GetInputResources( spirv_cross::CompilerGLSL& gl, spirv_cross::SmallVector<spirv_cross::Resource>& res, std::vector<IOData>& block);

	ShaderData GetShaderData(std::string shaderPath);
};
