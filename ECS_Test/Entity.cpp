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

		template < typename T, Args && ... args >
		void Entity::AddComponent( Args && ... args )
		{
			T* component{std::forward<Args>(args)...};
			addComponent(component, ComponentId<T>());
		}

		template < typename T >
		void Entity::AddComponent( T component, std::uint32_t componentId)
		{
			GetWorld()._entityAttributes._componentPool.addComponent(GetId(), component, componentId);
		}
	}
}
