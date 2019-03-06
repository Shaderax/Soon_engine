#pragma once

#include "Entity.hpp"
#include "Id.hpp"

#include <iostream>

using namespace Soon::ECS;

namespace Soon
{
	namespace ECS
	{
		struct EntityCache
		{
			EntityCache( void );
			~EntityCache( void );

			std::vector< Id > _alive;
			std::vector< Id > _killed;
			std::vector< Id > _activated;
			std::vector< Id > _desactivated;
		};
	}
}
