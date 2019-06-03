#pragma once

#include "ECS/Component.hpp"
#include "ECS/Entity.hpp"
#include "Core/Math/vec3.hpp"

struct Transform3D : Component
{
	Transform3D( Entity& entity )
	{
		_pos = vec3<float>(0.0f, 0.0f, 0.0f);
		_rot = vec3<float>(0.0f, 0.0f, 0.0f);
		_scale = vec3<float>(1.0f, 1.0f, 1.0f);
	}
	
	vec3<float>	_pos;
	vec3<float>	_rot;
	vec3<float>	_scale;
};
