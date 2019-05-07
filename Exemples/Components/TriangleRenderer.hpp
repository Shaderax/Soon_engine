#include "ECS/Component.hpp"
#include "Core/Math/vec3.hpp"
#include "Core/Math/vec2.hpp"
#include "Graphics/"

class TriangleRenderer : Component
{
	public:
		TriangleRenderer( void )
		{
			bool isRenderable = true;

			if (isRenderable)
				GraphicsRenderer::GetInstance()->AddToRender(this);
		};

		~TriangleRenderer( void );

	private:
		const float[] = {0.0f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f};
};
