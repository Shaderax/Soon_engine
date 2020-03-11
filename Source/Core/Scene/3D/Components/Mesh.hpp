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
		public:
			Mesh( void )
			{
				_vertices = nullptr;
				_indices = nullptr;
			}

			Mesh(const Mesh& other)
			{
				_vertices = other._vertices;
				_indices = other._indices;

				// Set Vertex Description.

				//_path = other._path;
				//_material = other._material;
				//_active = other._active;
			}

			~Mesh( void )
			{

			}

			std::vector< Vertex >*		_vertices;
			std::vector<uint32_t>*		_indices;
	};
}
