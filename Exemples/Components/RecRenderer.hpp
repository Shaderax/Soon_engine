#include "ECS/Component.hpp"
#include "Core/Math/vec3.hpp"
#include "Graphics/Vulkan/GraphicsRenderer.hpp"
#include "Scene/3D/Components/Transform3D.hpp"

namespace Soon
{
	class RecRenderer : public Component
	{
		public:
			RecRenderer( Entity& entity )
			{
				bool isRenderable = true;

				if (isRenderable)
					_itRender = GraphicsRenderer::GetInstance()->AddToRender(entity.GetComponent<Transform3D>(), _inf);
			};

			~RecRenderer( void ) {};

			float _ui[6] = {0.0f, 1.0f, -0.5f, 0.5f, 0.5f, 0.5f};
			//                   B            G            D
		private:

			VertexBufferInfo _inf =
			{
				3,
				6 * sizeof(float),
				&_ui
			};

			ComponentRenderer _itRender;
	};
}
