#pragma once

#include "Scene/ComponentRenderer.hpp"
#include <vector>
#include <iostream>
#include "Utilities/Vertex.hpp"

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

			~Mesh( void )
			{

			}

			void EnableRender();
			void DisableRender();

			std::vector< Vertex >		_vertices;
			std::vector<uint32_t>		_indices;
			std::string			_path;

		private:
			Entity*				_owner;
	};
}
