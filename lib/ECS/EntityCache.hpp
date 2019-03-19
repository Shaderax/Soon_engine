#pragma once

#include "Id.hpp"
#include "Entity.hpp"

#include <iostream>
#include <vector>

using namespace Soon::ECS;

namespace Soon
{
	namespace ECS
	{
		struct EntityCache
		{
			void ClearTemp( void );

			void Clear( void );

			int ok = 50;

			std::vector< Entity > _alive;
			std::vector< Entity > _killed;
			std::vector< Entity > _activated;
			std::vector< Entity > _desactivated;
		};
	}
}
