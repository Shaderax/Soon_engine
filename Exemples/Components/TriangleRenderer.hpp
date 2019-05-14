#include "ECS/Component.hpp"
#include "Core/Math/vec3.hpp"
#include "Graphics/Vulkan/GraphicsRenderer.hpp"
#include "Scene/3D/Components/Transform3D.hpp"

namespace Soon
{
	class TriangleRenderer : public Component
	{
		public:
			TriangleRenderer( Entity& entity )
			{
				float ok[6] = {0.0f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f};
//				_ui = ok;
//				_ui = {0.0f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f};
				bool isRenderable = true;

				if (isRenderable)
					_itRender = GraphicsRenderer::GetInstance()->AddToRender(entity.GetComponent<Transform3D>(), _inf);
			};

			~TriangleRenderer( void ) {};

		private:
			float _ui[6] = {0.0f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f};

			VertexBufferInfo _inf =
			{
				3,
				6 * sizeof(float),
				&_ui
			};

			ComponentRenderer _itRender;
	};
}
