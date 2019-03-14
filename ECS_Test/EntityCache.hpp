#pragma once

#include "Id.hpp"

#include <iostream>

using namespace Soon::ECS;

namespace Soon
{
	namespace ECS
	{
		struct EntityCache
		{
			void ClearTemp( void )
			{
				_killed.clear();
				_activated.clear();
				_desactivated.clear();
			}

			void Clear( void )
			{
				_alive.clear();
				ClearTemp();
			}

			std::vector< Entity > _alive;
			std::vector< Entity > _killed;
			std::vector< Entity > _activated;
			std::vector< Entity > _desactivated;
		};
	}
}
