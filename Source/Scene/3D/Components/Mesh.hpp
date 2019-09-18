#pragma once

//#include "ECS/Component.hpp"
#include "Scene/ComponentRenderer.hpp"
#include "Core/Math/vec2.hpp"
#include "Core/Math/vec3.hpp"
#include <vector>
#include <iostream>
#include "Graphics/Vulkan/GraphicsRenderer.hpp"

#include "Scene/Common/Material.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

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

			void EnableRender( void );
			void DisableRender( void );

			VertexBufferInfo _inf =
			{
			};

//			ComponentRenderer _itRender;

			std::vector< Vertex >		_vertices;
			std::vector<uint32_t>		_indices;
			std::string					_path;

			Material			_mat;
		private:
			Entity*				_owner;
	};
}
