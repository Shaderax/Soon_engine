#pragma once

#include "Entity.hpp"

namespace Soon
{
	namespace ECS
	{
		class EntityPool
		{
			public:
				EntityPool( World& world );
				~EntityPool( void );

				Entity CreateEntity( void );

			private:
				std::uint32_t _nextId;
				std::vector<Entity> _entityPool;
		};
	}
}
