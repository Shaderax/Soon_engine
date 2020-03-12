#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "vulkan/vulkan.h"

#include <vector>

namespace Soon
{
enum struct PipelineType : uint32_t
{
	GRAPHIC = 0,
	COMPUTE = 1
};

enum class EnumShaderType : uint8_t
{
	UNKNOW = 0,
	VOID = 1,
	BOOLEAN = 2,
	SBYTE = 3,
	UBYTE = 4,
	SHORT = 5,
	USHORT = 6,
	INT = 7,
	UINT = 8,
	INT64 = 9,
	UINT64 = 10,
	ATOMICCOUNTER = 11,
	HALF = 12,
	FLOAT = 13,
	DOUBLE = 14,
	STRUCT = 15,
	IMAGE = 16,
	SAMPLEDIMAGE = 17,
	SAMPLER = 18,
	ACCELERATIONSTRUCTURENV = 19,

	// Keep internal types at the end.
	CONTROLPOINTARRAY = 20,
	CHAR = 21,
};

struct ShaderType
{
	EnumShaderType	type;
	uint32_t		length;
};

DataType SpirTypeToShaderType( spirv_cross::SPIRType type )
{
	DataType dt;
	dt.length = type.vecsize;

	switch (type.basetype)
	{
		case SPIRType::BaseType::Unknown :
			dt.type = EnumUniformsType::UNKNOW;
		case SPIRType::BaseType::Void :
			dt.type = EnumUniformsType::VOID;
		case SPIRType::BaseType::Boolean :
			dt.type = EnumUniformsType::BOOLEAN;
		case SPIRType::BaseType::SByte :
			dt.type = EnumUniformsType::SBYTE;
		case SPIRType::BaseType::UByte :
			dt.type = EnumUniformsType::UBYTE;
		case SPIRType::BaseType::Short :
			dt.type = EnumUniformsType::SHORT;
		case SPIRType::BaseType::UShort :
			dt.type = EnumUniformsType::USHORT;
		case SPIRType::BaseType::Int :
			dt.type = EnumUniformsType::INT;
		case SPIRType::BaseType::UInt :
			dt.type = EnumUniformsType::UINT;
		case SPIRType::BaseType::Int64 :
			dt.type = EnumUniformsType::UINT64;
		case SPIRType::BaseType::UInt64 :
			dt.type = EnumUniformsType::UINT64;
		case SPIRType::BaseType::AtomicCounter :
			dt.type = EnumUniformsType::ATOMICCOUNTER;
		case SPIRType::BaseType::Half :
			dt.type = EnumUniformsType::HALF;
		case SPIRType::BaseType::Float :
			dt.type = EnumUniformsType::FLOAT;
		case SPIRType::BaseType::Double :
			dt.type = EnumUniformsType::DOUBLE;
		case SPIRType::BaseType::Struct :
			dt.type = EnumUniformsType::STRUCT;
		case SPIRType::BaseType::Image :
			dt.type = EnumUniformsType::IMAGE;
		case SPIRType::BaseType::SampledImage :
			dt.type = EnumUniformsType::SAMPLEDIMAGE;
		case SPIRType::BaseType::Sampler :
			dt.type = EnumUniformsType::SAMPLER;
		case SPIRType::BaseType::AccelerationStructureNV :
			dt.type = EnumUniformsType::ACCELERATIONSTRUCTURENV;
		case SPIRType::BaseType::ControlPointArray :
			dt.type = EnumUniformsType::CONTROLPOINTARRAY;
		case SPIRType::BaseType::Char :
			dt.type = EnumUniformsType::CHAR;
	}
	return (dt);
}

struct UniformVar
{
	std::string _name;
	ShaderType _type;
	uint32_t _size;
	uint32_t _offset;
};

struct Uniform
{
	std::string _name;
	uint32_t _size;
	uint32_t _binding;
	uint32_t _set;
	std::vector<UniformVar> _members;
	std::vector<UniformSets> _us;
};

struct InputVar
{
	std::string _name;
	ShaderType _type;
	uint32_t _location;
};

struct UniformsTexture
{
	UniformVar _data;
	uint32_t _binding;
	uint32_t _set;
	std::vector<Image> _i;
	std::vector<ImageRenderer> _iR;
	std::vector<VkDescriptorSet> _dS;
};

class BasePipeline
{
private:
	std::vector<VkDescriptorSetLayout> _descriptorSetLayout;
	VkPipelineLayout	_pipelineLayout;
	VkPipeline			_graphicPipeline;
	std::vector<uint32_t> _toDraw;
	VertexDescription	_vertexDescription;

	std::vector<UniformsTexture> _uniformsTexture; // uniformSampler2D
	std::vector<Uniform> _uniforms;				   // uniformModel, uniformLight
	std::vector<InputVar> _inputs;				   // inPosition
public:
	BasePipeline(void)
	{
	}

	virtual ~BasePipeline() {}
	virtual std::vector<VkDescriptorSetLayoutBinding> GetLayoutBinding(void) = 0;
	virtual void UpdateData(int currentImg) = 0;
	virtual void BindCaller(VkCommandBuffer commandBuffer, uint32_t index) = 0;
	//		virtual std::vector<VkVertexInputAttributeDescription> GetAttributeDescriptions( void ) = 0;
	//		virtual VkVertexInputBindingDescription GetBindingDescription( void ) = 0;
	virtual void RecreateUniforms(void) = 0;
	virtual void RecreatePipeline(void) = 0;

	virtual void Render(uint32_t id) = 0;
	virtual void UnRender(uint32_t id) = 0;

	virtual uint32_t AddToPipeline(Transform3D &transform, Mesh *mesh) = 0;
	virtual void RemoveFromPipeline(uint32_t id) = 0;

	void ProcessShaderData(SpirvReader::ShaderData sData)
	{
		for (SpirvReader::IOData &data : sData.input)
		{
			InputVar input;
			input._name = data.name;
			input._location = data.location;

			if (data.type.vecsize > 1 && data.type.columns == 1)
				input._type = (EnumUniformsType)((uint8_t)EnumUniformsType::VECTOR2 + data.type.vecsize - 2);
			else if (data.type.vecsize > 1 && data.type.columns > 1)
				input._type = (EnumUniformsType)((uint8_t)EnumUniformsType::MAT2 + data.type.columns - 2);
			else
				input._type = (EnumUniformsType)data.type.basetype;

			_inputs.push_back(input);
		}

		for (SpirvReader::Block &block : sData.data)
		{
			if (block.isTexture)
			{
				UniformsTexture texture;
				texture._binding = block.binding;
				texture._set = block.set;
				texture._data._name = block.name;
				texture._data._type = (EnumUniformsType)block._type.basetype;
				_uniformsTexture.push_back(texture);
			}
			else
			{
				Uniform uniform;
				uniform._name = block.name;
				uniform._binding = block.binding;
				uniform._set = block.set;
				uniform._size = block.size;
				for (SpirvReader::Member &member : block.members)
				{
					UniformVar uniVar;
					uniVar._name = member.name;
					uniVar._offset = member.offset;
					uniVar._size = member.size;
					if (member._type.vecsize > 1 && member._type.columns == 1)
						uniVar._type = (EnumUniformsType)((uint8_t)EnumUniformsType::VECTOR2 + member._type.vecsize - 2);
					else if (member._type.vecsize > 1 && member._type.columns > 1)
						uniVar._type = (EnumUniformsType)((uint8_t)EnumUniformsType::MAT2 + member._type.columns - 2);
					else
						uniVar._type = (EnumUniformsType)member._type.basetype;
					uniform._members.push_back(uniVar);
				}
				_uniforms.push_back(uniform);
			}
		}
	}
};
} // namespace Soon