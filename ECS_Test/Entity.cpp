#include "Entity.hpp"
#include "World.hpp"
#include "Id.hpp"
#include "Component.hpp"
#include "Config.hpp"

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
			ECS_ASSERT(_world, "world in entity is null");

			return (*_world);
		}

		TypeId Entity::GetId( void ) const
		{
			return (_id.GetId());
		}

		Id Entity::GetIdClass( void ) const
		{
			return (_id);
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
			if (_world == nullptr)
				return (false);
			return (GetWorld().IsValid(GetIdClass()));
		}

		template < typename T >
			bool Entity::HasComponent( TypeId componentId ) const
			{
				return (GetWorld()._entityAttributes._componentPool.HasComponent(GetIdClass(), componentId));
			}

		void Entity::RemoveAllComponents( void )
		{
			GetWorld()._entityAttributes._componentPool.RemoveAllEntityComponents(GetIdClass());
		}

		void Entity::RemoveComponent( TypeId componentTypeId )
		{
			GetWorld()._entityAttributes._componentPool.RemoveComponent(GetIdClass(), componentTypeId);
		}

		Component& Entity::GetComponent( TypeId componentTypeId ) const
		{
			return (GetWorld()._entityAttributes._componentPool.GetComponent(GetIdClass(), componentTypeId));
		}
	}
}
