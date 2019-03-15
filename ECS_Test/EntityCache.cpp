#include "EntityCache.hpp"

namespace Soon
{
	namespace ECS
	{
		void EntityCache::ClearTemp( void )
		{
			_killed.clear();
			_activated.clear();
			_desactivated.clear();
		}

		void EntityCache::Clear( void )
		{
			_alive.clear();
			ClearTemp();
		}
	}
}
