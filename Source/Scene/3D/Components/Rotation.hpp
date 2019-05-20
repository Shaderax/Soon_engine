#pragma once

#include "ECS/Component.hpp"
#include "ECS/Entity.hpp"

struct Rotation3D : Component
{
	Rotation3D( Entity& entity )
	{

	}

	float x;
	float y;
	float z;
};
