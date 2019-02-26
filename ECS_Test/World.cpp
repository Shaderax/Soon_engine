#include "World.hpp"
#include <iostream>

namespace Soon
{
	namespace ECS
	{
		World::World( void )
		{
		}

		World::~World( void )
		{
		}

		Entity World::CreateEntity( void )
		{
			CheckResizePool(1);

			_entityCache.alive.push_back(_entityPool.CreateEntity());
			return (_entityCache.alive.back());
		}

		EntityPool World::GetEntityPool( void )
		{
			return (_entityPool);
		}

		std::size_t World::GetAliveEntityCount( void ) const
		{
			return (_entityCache.alive.size());
		}

		void World::Resize( std::size_t amount )
		{
			_entityPool.Resize();
		}

		std::size_t World::GetEntityCount( void ) const
		{
			return (_entityPool.GetEntityCount());
		}

		void World::CheckResizePool( std::size_t amount )
		{
			std::size_t newSize = GetAliveEntityCount() + amount;

			if (newSize > GetEntityCount())
				Resize(newSize);
		}
	}
}
