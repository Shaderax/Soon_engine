#pragma once

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
				std::vector<Entity> alive;
				std::vector<Entity> killed;
				std::vector<Entity> activated;
				std::vector<Entity> deactivated;
		}
	}
}
