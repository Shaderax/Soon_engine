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
		FLOAT2 = 0,
		FLOAT3 = 1
	};

	struct VertexElement
	{
		VertexElementSementic sementic;
		VertexType type;
	};

	struct VertexDescription
	{
		std::vector<VertexElement> data;

		bool HasElement( void )
		{
			for (VertexElement& element : data)
			{
			}
			return (false);
		}

		void AddVertexElement( VertexElementSementic sem, VertexType type )
		{
			assert(!HasElement(sem, type) && "Has Element");

			for (VertexElement& element : data)
			{
			}
		}

		void RemoveVertexElement( void )
		{

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

		void SetVertexElement( uint8_t* data, VertexElement elem )
		{

		}
	};
}