#include "EntityPool.hpp"
#include <iostream>

namespace Soon
{
	namespace ECS
	{
		Entity EntityPool::CreateEntity( void )
		{
			Entity e(_nextId);

			_nextId++;
			return (e);
		}

		std::size_t EntityPool::GetEntityCount( void )
		{
			return (_nextId);
		}
		
		void EntityPool::Resize( std::size_t amount )
		{
			
		}
	}
}
