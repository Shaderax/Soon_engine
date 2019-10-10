#pragma once

#include "ECS/Component.hpp"
#include "Scene/Common/ShaderMaterial.hpp"

namespace Soon
{
	class ComponentRenderer : public Component
	{
		public:
			ShaderMaterial	_material;
			bool		_active;

			ComponentRenderer( void ) : _active(false)
			{

			}

			virtual ~ComponentRenderer( void ) {};

			virtual void EnableRender( void ) = 0;
			virtual void DisableRender( void ) = 0;
	};
}
