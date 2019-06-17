#pragma once

#include "ECS/Component.hpp"
#include "ECS/Entity.hpp"
#include "Graphics/Vulkan/GraphicsRenderer.hpp"

namespace Soon
{
	class DirectionalLight : public Component
	{
		public:

		DirectionalLight( Entity& entity ) : _direction(0.0f, -1.0f, 0.0f), _intensity(1.0f), _lightColor(1.0f, 1.0f, 1.0f)
		{
			GraphicsRenderer::GetInstance()->AddLightToRender(entity.GetComponent<Transform3D>(), this);
		}

			~DirectionalLight( void )
			{

			}

			vec3<float> _direction;
			vec3<float>	_lightColor;
			float _intensity;
	};
}
