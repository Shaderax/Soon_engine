#include "ECS/Component.hpp"
#include "Core/Math/vec3.hpp"
#include "Core/Math/vec2.hpp"
#include "Graphics/GLFW/GLFWVulkan/GLFWVulkanRenderer.hpp"

class TriangleRenderer : Component
{
	public:
		TriangleRenderer( Entity& entity )
		{
			bool isRenderable = true;

			if (isRenderable)
				_itRender = GraphicsRenderer::GetInstance()->AddToRender(entity.GetComponent<Transform>(), _inf);
		};

		~TriangleRenderer( void );

	private:
		const float _ui[] = {0.0f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f};

		VertexBufferInfo _inf =
		{
			3,
			6 * sizeof(float),
			&_ui;
		};

		ComponentRenderer _itRender;
};
