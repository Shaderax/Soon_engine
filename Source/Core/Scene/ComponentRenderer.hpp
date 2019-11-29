#pragma once

#include "ECS/Entity.hpp"
#include "ECS/Component.hpp"
#include "Core/Scene/Materials/ShaderMaterial.hpp"

namespace Soon
{
	class ComponentRenderer : public Component
	{
		public:
			Entity*		_owner;
			ShaderMaterial	_material;
			bool		_active;

			ComponentRenderer( void );
			~ComponentRenderer( void );

			void Enable( void );
			void Disable( void );
	};
}
