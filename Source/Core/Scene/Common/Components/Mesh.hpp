#pragma once

#include <vector>
#include <string>
#include "Core/Scene/ComponentRenderer.hpp"
#include "Utilities/Vertex.hpp"
#include "ECS/Entity.hpp"

namespace Soon
{
class Mesh : public ComponentRenderer
{
private:
	VertexDescription _vertexDescription;
	uint8_t* _vertexData;
	uint8_t* _indices;
	uint32_t _numIndices;
	uint32_t _numVertex;
	//std::vector<Vertex> *_vertices;
	//std::vector<uint32_t> *_indices;

public:
	Mesh(VertexDescription v)
	{
		_vertexDescription = v;
	}

	Mesh(const Mesh &other)
	{
		_vertices = other._vertices;
		_indices = other._indices;

		// Set Vertex Description.
	}

	~Mesh(void)
	{
	}

	// Loader Free ?

	void SetVertexElement(uint8_t* data, uint32_t size, VertexElement elem)
	{
		assert(!_vertexDescription.HasElement(sem, type) && "Has Element");

		uint32_t elementSize = elem.GetTypeSize();
		uint32_t offset = _vertexDescription.GetElementOffset(elem.sementic, elem.type);
		uint32_t strideSize = _vertexDescription.GetVertexStrideSize();

		for (uint32_t index = 0; index < _numVertex; index++)
		{
			memcpy(_vertexData + (index * strideSize) + offset, data + (index * elementSize), elementSize);
		}
	}
};
}; // namespace Soon