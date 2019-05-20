#pragma once

#include "ECS/Component.hpp"
#include "ECS/Entity.hpp"

struct Position3D : Component
{
	Position3D( Entity& entity )
	{

	}

	float x;
	float y;
	float z;
};
