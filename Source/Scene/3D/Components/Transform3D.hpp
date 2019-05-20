#pragma once

#include "ECS/Component.hpp"
#include "ECS/Entity.hpp"

struct Transform3D : Component
{
	Transform3D( Entity& entity )
	{
		_scale = vec3(1.0f, 1.0f, 1.0f);;
	}
	
	vec3<float>	_pos;
	vec3<float>	_rot;
	vec3<float>	_scale;
};
