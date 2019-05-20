#include "ECS/Component.hpp"
#include "Core/Math/vec2.hpp"
#include "Core/Math/vec3.hpp"
#include <vector>
#include <iostream>
#include "Graphics/Vulkan/GraphicsRenderer.hpp"

namespace Soon
{
	class ObjFile : public Component
	{
		public:
			~ObjFile() {};
			void LoadObjFile(std::string path);

			ObjFile(Entity& entity)
			{
				_owner = entity;
				//			if (1)
				//				_itRender = GraphicsRenderer::GetInstance()->AddToRender(entity.GetComponent<Transform3D>(), _inf);

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
