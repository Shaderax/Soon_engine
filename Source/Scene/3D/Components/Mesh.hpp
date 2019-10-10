#pragma once

//#include "ECS/Component.hpp"
#include "Scene/ComponentRenderer.hpp"
#include "Core/Math/vec2.hpp"
#include "Core/Math/vec3.hpp"
#include <vector>
#include <iostream>
//#include "Graphics/Vulkan/GraphicsRenderer.hpp"

//#include "Scene/Common/Material.hpp"
//
//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>

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

			void EnableRender( void )
			{
				if (_owner && _material._shaderPipeline)
					_material._shaderPipeline->AddToRender(_owner->GetComponent<Transform3D>(), this);
			};

			void DisableRender( void )
			{
//				if (_material._shaderPipeline)
//					_material._shaderPipeline->RemoveRender();
			};

//			ComponentRenderer _itRender;

			std::vector< Vertex >		_vertices;
			std::vector<uint32_t>		_indices;
			std::string			_path;

		private:
			Entity*				_owner;
	};
}
