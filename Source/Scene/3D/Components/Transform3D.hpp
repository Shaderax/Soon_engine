#pragma once

#include "ECS/Component.hpp"
#include "ECS/Entity.hpp"

struct Transform3D : Component
{
	Transform3D( Entity& entity )
	{

	}

	float x;
	float y;
	float z;
};
