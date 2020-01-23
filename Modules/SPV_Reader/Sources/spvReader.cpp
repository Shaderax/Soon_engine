#include "spvReader.hpp"
#include <spirv_glsl.hpp>
#include <fstream>
#include <vector>
#include <iostream>

static std::vector<std::uint32_t> ReadFile(const std::string& filename)
{
	std::ifstream file(filename, std::ios::ate | std::ios::binary);

	if (!file.is_open())
	{
		throw std::runtime_error("failed to open file!" + filename);
	}

	size_t fileSize = (size_t) file.tellg();
	std::vector<std::uint32_t> buffer(fileSize / sizeof(std::uint32_t));

	file.seekg(0);
	file.read(reinterpret_cast<char*>(buffer.data()), fileSize);

	file.close();

	return buffer;
}

namespace SpirvReader
{
	void GetTexturesUniformsResources( spirv_cross::CompilerGLSL& gl, spirv_cross::SmallVector<spirv_cross::Resource>& res, std::vector<Block>& blocks)
	{
		for ( auto& ressource : res )
		{
			Block block;
			unsigned set = gl.get_decoration(ressource.id, spv::DecorationDescriptorSet);
			unsigned binding = gl.get_decoration(ressource.id, spv::DecorationBinding);
			const spirv_cross::SPIRType& ub_type = gl.get_type(ressource.base_type_id);

			spirv_cross::SmallVector<spirv_cross::BufferRange> ranges = gl.get_active_buffer_ranges(ressource.id);
			printf("%s at set %u, binding %u\n", ressource.name.c_str(), set, binding);

			block.isTexture = true;
			block.set = set;
			block.name = ressource.name;
			block.binding = gl.get_decoration(ressource.id, spv::DecorationBinding);
			blocks.push_back(block);
		}
	}

	void GetUniformsResources( spirv_cross::CompilerGLSL& gl, spirv_cross::SmallVector<spirv_cross::Resource>& res, std::vector<Block>& blocks)
	{
		for ( auto& ressource : res )
		{
			Block block;
			unsigned set = gl.get_decoration(ressource.id, spv::DecorationDescriptorSet);
			unsigned binding = gl.get_decoration(ressource.id, spv::DecorationBinding);
			const spirv_cross::SPIRType& ub_type = gl.get_type(ressource.base_type_id);

			spirv_cross::SmallVector<spirv_cross::BufferRange> ranges = gl.get_active_buffer_ranges(ressource.id);
			printf("%s at set %u, binding %u\n", ressource.name.c_str(), set, binding);

			for (auto& range : ranges)
			{
				Member member;
				member.name = gl.get_member_name(ressource.base_type_id, range.index);
				member.size = range.range;
				member.offset = range.offset;
				block.members.push_back(member);
				std::cout << ressource.name << "." << member.name << std::endl;
			}

			block.set = set;
			block.name = ressource.name;
			block.size = gl.get_declared_struct_size(ub_type);
			block.binding = gl.get_decoration(ressource.id, spv::DecorationBinding);
			block.isTexture = false;
			blocks.push_back(block);
		}
	}

	void GetInputResources( spirv_cross::CompilerGLSL& gl, spirv_cross::SmallVector<spirv_cross::Resource>& res, std::vector<IOData>& block)
	{
		for ( auto& ressource : res )
		{
			unsigned location = gl.get_decoration(ressource.id, spv::DecorationLocation);
			const spirv_cross::SPIRType& ub_type = gl.get_type(ressource.base_type_id);

			IOData data;
			data.name = ressource.name;
			data.location = location;
			data.type = ub_type;
			block.push_back(data);
			printf("%s at location %u\n", ressource.name.c_str(), location);
		}
	}

	ShaderData GetShaderData(std::string shaderPath)
	{
		ShaderData shaderData;
		std::vector<std::uint32_t> spirvFile = ReadFile(shaderPath);

		spirv_cross::CompilerGLSL gl(std::move(spirvFile));

		spirv_cross::ShaderResources res = gl.get_shader_resources();

		GetTexturesUniformsResources(gl, res.sampled_images, shaderData.data);
		GetUniformsResources(gl, res.uniform_buffers, shaderData.data);
		GetInputResources(gl, res.stage_inputs, shaderData.input);
		//(res.push_constant_buffers);
		//(res.storage_buffers);
		//(res.stage_outputs);


		return (shaderData);
	}
};
