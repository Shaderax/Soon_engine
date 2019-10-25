#pragma once

#include "Core/Scene/ComponentRenderer.hpp"
#include <vector>
#include <string>
#include "Utilities/Vertex.hpp"
#include "ECS/Entity.hpp"

namespace Soon
{
	// Vertex of a 3D Object
	class Mesh : public ComponentRenderer
	{
		public:
			Mesh( void ) : _owner(nullptr)
			{
			}

			Mesh(Entity& entity) : _owner(&entity)
			{
			}

			Mesh(const Mesh& other)
			{
				_vertices = other._vertices;
				_indices = other._indices;
				_path = other._path;
				_material = other._material;
				_active = other._active;
			}

			Mesh(Entity& entity, const Mesh& other) : _owner(&entity)
			{
				_vertices = other._vertices;
				_indices = other._indices;
				_path = other._path;
				_material = other._material;
				_active = other._active;
			}

			~Mesh( void )
			{

			}

			/*
			Mesh& operator=(const Mesh& other)
			{
				_vertices = other._vertices;
				_indices = other._indices;
				_path = other._path;

				return *this;
			}
			*/

			void EnableRender();
			void DisableRender();

			std::vector< Vertex >		_vertices;
			std::vector<uint32_t>		_indices;
			std::string			_path;

		private:
			Entity*				_owner;
	};
}
