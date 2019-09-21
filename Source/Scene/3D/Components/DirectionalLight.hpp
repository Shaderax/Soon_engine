#pragma once

#include "ECS/Component.hpp"
#include "ECS/Entity.hpp"
#include "Graphics/Vulkan/GraphicsRenderer.hpp"

namespace Soon
{
	struct DirectionalLight : public ComponentRenderer
	{
		DirectionalLight( Entity& entity ) : _direction(0.0f, 1.0f, 0.0f),  _lightColor(1.0f, 1.0f, 1.0f), _intensity(0.1f)
		{
//			GraphicsRenderer::GetInstance()->AddLightToRender(entity.GetComponent<Transform3D>(), this);
		}

			~DirectionalLight( void )
			{

			}

			alignas(16) vec3<float> _direction;
			alignas(16) vec3<float>	_lightColor;
			alignas(4) float _intensity;
	};
}
