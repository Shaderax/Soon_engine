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

	enum class VertexType : uint16_t
	{
		FLOAT = 0,
		FLOAT2 = 1,
		FLOAT3 = 2
	};

	struct VertexElement
	{
		VertexElementSementic sementic;
		VertexType type;

		uint32_t GetTypeSize( VertexType type )
		{
			switch (type)
			{
				case VertexType::FLOAT :
					return (sizeof(float));
				case VertexType::FLOAT2 :
					return (sizeof(float) * 2);
				case VertexType::FLOAT3 :
					return (sizeof(float) * 3);
				default :
					break ;
			}
		}
		return (0);
	};

	struct VertexDescription
	{
		std::vector<VertexElement> data;
		uin32_t strideSize;

		bool HasElement( VertexElementSementic sem, VertexType type )
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

		void AddVertexElement( VertexElementSementic sem, VertexType type )
		{
			assert(!HasElement(sem, type) && "Has Element");

			VertexElement vd;
			vd.sementic = sem;
			vd.type = type;
			data.push_back(vd);
			strideSize += vd.GetTypeSize();
		}

		void RemoveVertexElement( VertexElementSementic sem )
		{
			assert(!HasElement(sem, type) && "Has Element");

			for (VertexElement& element : data)
			{
				if (element.sementic == sem)
				{
					strideSize -= element.GetTypeSize();
					data.erase(element);
				}
			}
		}

		uin32_t GetVertexStrideSize( void )
		{
			return (strideSize);
		}

		uint32_t GetElementOffset( VertexElementSementic sem, VertexType type )
		{
			assert(!HasElement(sem, type) && "Has Element");

			uin32_t offset = 0;

			for (VertexElement& element : data)
			{
				if (sem == element.sementic)
					break ;
				offset += element.GetTypeSize(element.type)
			}
			return (offset);
		}
	};

	class Vertex // Mesh
	{
		private:
			VertexDescription _vertexDescription;
			uint8_t* _vertexData;
			uint8_t* _indices;
			uint32_t _numIndices;
			uint32_t _numVertex;

		public:
		Vertex( VertexDescription v )
		{
			_vertexDescription = v;
		}

		void SetVertexElement( uint8_t* data, uint32_t size, VertexElement elem )
		{
			assert(!_vertexDescription.HasElement(sem, type) && "Has Element");

			uint32_t elementSize = elem.GetTypeSize();
			uint32_t offset = _vertexDescription.GetElementOffset( elem.sementic, elem.type );
			uint32_t strideSize = _vertexDescription.GetVertexStrideSize();

			for (uint32_t index = 0 ; index < _numVertex ; index++)
			{
				memcpy(_vertexData + (index * strideSize) + offset, data + (index * elementSize), elementSize);
			}
		}
	};
}