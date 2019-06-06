#include "ECS/Component.hpp"
#include "Core/Math/vec2.hpp"
#include "Core/Math/vec3.hpp"
#include <vector>
#include <iostream>
#include "Graphics/Vulkan/GraphicsRenderer.hpp"

namespace Soon
{
	class Mesh : public Component
	{
		public:
			~Mesh() {};
			void LoadMesh(std::string path);

			Mesh(Entity& entity)
			{
				_owner = entity;
			};

			VertexBufferInfo _inf =
			{
				0,
				0,
				(void*)0
			};

			ComponentRenderer _itRender;
		private:
			Entity				_owner;

			std::vector< vec3<float> >	_vertex;
			std::vector< vec2<float> >	_vectexTexture;
			std::vector< vec3<float> >	_normal;
	};
}
