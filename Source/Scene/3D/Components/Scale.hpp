#pragma once

#include "ECS/Component.hpp"
#include "ECS/Entity.hpp"

struct Scale3D : Component
{
	Scale3D( Entity& entity )
	{

	}

	float x;
	float y;
	float z;
};
