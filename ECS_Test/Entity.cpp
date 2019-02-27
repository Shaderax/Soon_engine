#include <iostream>
#include "Entity.hpp"
#include "World.hpp"

namespace Soon
{
	namespace ECS
	{
		Entity::Entity( World* world, std::uint32_t id ) :
			_id(id),
			_world(world)
		{
		}

		Entity::~Entity( void )
		{
			
		}

		World& Entity::GetWorld( void ) const
		{
			return (*_world);
		}

		bool Entity::IsActivated( void ) const
		{
			return (GetWorld().IsActivated(_id));
		}

		void Entity::Kill( void )
		{
			GetWorld().KillEntity(*this);
		}
		
		void Entity::Kill( void )
		{
			GetWorld().KillEntity(GetIdClass());
		}
	}
}
