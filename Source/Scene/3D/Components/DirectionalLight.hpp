#pragma once

#include "ECS/Component.hpp"
#include "ECS/Entity.hpp"
//#include "Graphics/Vulkan/GraphicsRenderer.hpp"

#include "Scene/Common/Light.hpp"

namespace Soon
{
	struct DirectionalLight : public Light
	{
		DirectionalLight( Entity& entity )
		{
			_type = LightType::DIRECTIONAL;
//			GraphicsRenderer::GetInstance()->AddLight(entity.GetComponent<Transform3D>(), this);
		}

			~DirectionalLight( void )
			{

			}

//			alignas(16) vec3<float> _direction;
//			alignas(16) vec3<float>	_lightColor;
//			alignas(4) float _intensity;
	};
}
