#pragma once

#include "ECS/Component.hpp"
#include "ECS/Entity.hpp"

namespace Soon
{
	struct ParticlesSystem : public Component
	{
		public:
			ParticlesSystem( Entity& entity );

			~ParticlesSystem( void );

			uint32_t _size;
	};
}
