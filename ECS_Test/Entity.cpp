#include "Entity.hpp"
#include "World.hpp"
#include "Id.hpp"
#include "Component.hpp"

#include <iostream>

namespace Soon
{
	namespace ECS
	{
		Entity::Entity( World& world, TypeId id ) :
			_id(id),
			_world(&world)
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

		void Entity::Activate( void )
		{
			GetWorld().ActivateEntity(GetIdClass());
		}

		void Entity::Desactivate( void )
		{
			GetWorld().DesactivateEntity(GetIdClass());
		}

		void Entity::Kill( void )
		{
			GetWorld().KillEntity(GetIdClass());
		}

		void Entity::AddComponent( Component* component, TypeId componentId)
		{
			GetWorld()._entityAttributes._componentPool.AddComponent(GetIdClass(), component, componentId);
		}

		bool Entity::IsValid( void ) const
		{
			return (GetWorld().IsValid(GetIdClass()));
		}

		template < typename T >
			bool Entity::HasComponent( TypeId componentId ) const
			{
				return (GetWorld()._entityAttributes._componentPool.HasComponent(GetIdClass(), componentId));
			}
	}
}
