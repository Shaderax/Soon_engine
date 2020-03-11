#pragma once

#include "ECS/Entity.hpp"
#include "ECS/Component.hpp"
#include "Core/Scene/Materials/ShaderMaterial.hpp"

namespace Soon
{
	class ComponentRenderer : public Component
	{
		public:
			// No ptr for destructor
			ShaderMaterial	_material;

			ComponentRenderer( void );
			virtual ~ComponentRenderer( void );

			void Enable( void );
			void Disable( void );
	};
}
