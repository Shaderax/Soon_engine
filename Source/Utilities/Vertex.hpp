#pragma once

#include "Math/vec3.hpp"
#include <vector>

namespace Soon
{
	enum class VertexElementSementic : uint16_t
	{
		POSITION = 1, /**< Position */
		//VES_BLEND_WEIGHTS = 2, /**< Blend weights */
		//VES_BLEND_INDICES = 3, /**< Blend indices */
		NORMAL = 2, /**< Normal */
		//VES_COLOR = 5, /**< Color */
		TEXCOORD = 4, /**< UV coordinate */
		//VES_BITANGENT = 7, /**< Bitangent */
		//VES_TANGENT = 8, /**< Tangent */
		//VES_POSITIONT = 9, /**< Transformed position */
		//VES_PSIZE = 10 /**< Point size */
	};

	struct VertexElement
	{
		VertexElementSementic sementic;
		ShaderType type;

		uint32_t GetTypeSize( ShaderType type )
		{
			switch (type.type)
			{
				case EnumShaderType::BOOLEAN :
					return (sizeof(bool) * type.length);
				case EnumShaderType::SBYTE :
					return (sizeof(uint8_t) * type.length);
				case EnumShaderType::UBYTE :
					return (sizeof(uint8_t) * type.length);
				case EnumShaderType::SHORT :
					return (sizeof(uint16_t) * type.length);
				case EnumShaderType::USHORT :
					return (sizeof(uint16_t) * type.length);
				case EnumShaderType::INT :
					return (sizeof(uint32_t) * type.length);
				case EnumShaderType::UINT :
					return (sizeof(uint32_t) * type.length);
				case EnumShaderType::INT64 :
					return (sizeof(uint64_t) * type.length);
				case EnumShaderType::UINT64 :
					return (sizeof(uint64_t) * type.length);
				case EnumShaderType::ATOMICCOUNTER :
					return (sizeof(uint32_t) * type.length);
				case EnumShaderType::HALF :
					return (sizeof(uint16_t) * type.length);
				case EnumShaderType::FLOAT :
					return (sizeof(float) * type.length);
				case EnumShaderType::DOUBLE :
					return (sizeof(double) * type.length);
				default :
					break ;
			}
		return (0);
		}
	};

	struct VertexDescription
	{
		std::vector<VertexElement> data;
		uin32_t strideSize;

		bool HasElement( VertexElementSementic sem, EnumShaderType type, uint32_t length )
		{
			for (VertexElement& element : data)
			{
				if (element.sementic == sem)
				{
					return (true);
				}
			}
			return (false);
		}

		void AddVertexElement( VertexElementSementic sem, EnumShaderType type, uint32_t length )
		{
			assert(!HasElement(sem, type) && "Has Element");

			VertexElement vd;
			vd.sementic = sem;
			vd.type.type = type;
			vd.type.length = length;
			data.push_back(vd);
			strideSize += vd.GetTypeSize();
		}

		void RemoveVertexElement( VertexElementSementic sem, EnumShaderType type )
		{
			assert(!HasElement(sem, type) && "Has Element");

			for (VertexElement& element : data)
			{
				if (element.sementic == sem)
				{
					strideSize -= element.GetTypeSize(element.type);
					data.erase(element);
				}
			}
		}

		uin32_t GetVertexStrideSize( void )
		{
			return (strideSize);
		}

		uint32_t GetElementOffset( VertexElementSementic sem, EnumShaderType type )
		{
			assert(!HasElement(sem, type) && "Has Element");

			uin32_t offset = 0;

			for (VertexElement& element : data)
			{
				if (sem == element.sementic)
					break ;
				offset += element.GetTypeSize(element.type.type)
			}
			return (offset);
		}
	};
}