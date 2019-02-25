#pragma once

#include "Ecs.hpp"

namespace Soon
{
	namespace ECS
	{
		class Entity
		{
			public:
				Entity( void );
				~Entity( void );

			private:
				// Check if 32 is faster
				std::uint32_t	_id;
				std::Bitset<MAX_COMPONENT> _bitset;
		};
	}
}
