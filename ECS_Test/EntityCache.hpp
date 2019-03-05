#pragma once

#include "Entity.hpp"
#include <iostream>

using namespace Soon::ECS;

namespace Soon
{
	namespace ECS
	{
		class EntityCache
		{
			public:
				EntityCache( void );
				~EntityCache( void );

			private:
				std::vector< Entity::Id > alive;
				std::vector< Entity::Id > killed;
				std::vector< Entity::Id > activated;
				std::vector< Entity::Id > deactivated;
		};
	}
}
