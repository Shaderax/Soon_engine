#pragma once

#include <vector>
#include <string>
#include "Core/Scene/ComponentRenderer.hpp"
#include "Utilities/Vertex.hpp"
#include "ECS/Entity.hpp"

namespace Soon
{
	// Vertex of a 3D Object
	class Mesh : public ComponentRenderer
	{
		public:
			Mesh( void )
			{
				_owner = nullptr;
				_vertices = nullptr;
				_indices = nullptr;
			}

			Mesh(Entity& entity)
			{
				_owner = &entity;
				_vertices = nullptr;
				_indices = nullptr;
			}

			Mesh(const Mesh& other)
			{
				_vertices = other._vertices;
				_indices = other._indices;
				//_path = other._path;
				//_material = other._material;
				_active = other._active;
			}

			/*
			Mesh(Entity& entity, const Mesh& other)
			{
				_owner = &entity;
				_vertices = other._vertices;
				_indices = other._indices;
				//_path = other._path;
				_material = other._material;
				_active = other._active;
			}
			*/

			~Mesh( void )
			{

			}

			std::vector< Vertex >*		_vertices;
			std::vector<uint32_t>*		_indices;
	};
}
