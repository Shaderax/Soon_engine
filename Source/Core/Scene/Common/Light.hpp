#pragma once

#include "Core/Math/vec3.hpp"

namespace Soon
{
	enum struct LightType : int8_t
	{
		POINT = 0,
		DIRECTIONAL = 1,
		SPOT = 2
	};

	class Light
	{
		public:
			Light( void ) : _lightColor(1.0f, 1.0f, 1.0f), _intensity(1.0f), _type(LightType::POINT) {};

			virtual ~Light( void );

		private:
			LightType	_type;
			float _intensity;
			vec3<float> _lightColor;
	};
}
