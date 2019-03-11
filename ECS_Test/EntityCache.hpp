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

			std::vector< Id > _alive;
			std::vector< Id > _killed;
			std::vector< Id > _activated;
			std::vector< Id > _desactivated;
		};
	}
}
