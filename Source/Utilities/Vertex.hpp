#pragma once

#include "Core/Math/vec3.hpp"

namespace Soon
{
	struct Vertex
	{
		vec3<float> _position;
		vec3<float> _normal;
		vec3<float> _texCoords;
	};
}
