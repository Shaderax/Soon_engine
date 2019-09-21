#pragma once

#include "ECS/Component.hpp"
#include "Scene/Common/Material.hpp"

namespace Soon
{
	class ComponentRenderer : public Component
	{
		public:
			Material _material;

			virtual ~ComponentRenderer( void ) {};

			virtual void EnableRender( void ) = 0;
			virtual void DisableRender( void ) = 0;
	};
}
