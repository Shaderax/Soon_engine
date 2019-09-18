#pragma once

#include "ECS/Component.hpp"

namespace Soon
{
	class ComponentRenderer : public Component
	{
		public:
			virtual ~ComponentRenderer( void ) {};

			virtual void EnableRender( void ) = 0;
			virtual void DisableRender( void ) = 0;
	};
}
