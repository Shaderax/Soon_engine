#pragma once

#include "Core/Math/vec3.hpp"

namespace Soon
{

	enum class LightType : int8_t
	{
		POINT = 0,
		DIRECTIONAL = 1;
		SPOT = 1;
	}

	class Light
	{
		public:
			Light( void ) : _lightColor(1.0f, 1.0f, 1.0f), _intensity(1.0f), _type(0) {};

			virtual ~Light( void );

		private:
			LightType	_type;
			vec3<float> _intensity;
			vec3<float> _lightColor;

	};
}
