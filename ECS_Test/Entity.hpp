#pragma once

#include "Ecs.hpp"

namespace Soon
{
	namespace ECS
	{
		class Entity
		{
			public:
				Entity( std::uint32_t id = 0 );
				~Entity( void );

				template< typename T > void AddComponent();


			private:
				// Check if 32 is faster
				std::uint32_t	_id;
		};
	}
}
