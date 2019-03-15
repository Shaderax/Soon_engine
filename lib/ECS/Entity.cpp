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
		Entity::Entity( void ) :
			_id(world.CreateEntityId())
		{
		}

		Entity::Entity( TypeId id ) :
			_id(id)
		{
		}

		Entity::~Entity( void )
		{

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
			return (world.IsActivated(*this));
		}

		void Entity::Activate( void )
		{
			world.ActivateEntity(*this);
		}

		void Entity::Desactivate( void )
		{
			world.DesactivateEntity(*this);
		}

		void Entity::Kill( void )
		{
			world.KillEntity(*this);
		}

		void Entity::AddComponent( Component* component, TypeId componentId)
		{
			world._entityAttributes._componentPool.AddComponent(*this, component, componentId);
		}

		bool Entity::IsValid( void ) const
		{
			return (world.IsValid(*this));
		}

		bool Entity::HasComponent( TypeId componentId ) const
		{
			return (world._entityAttributes._componentPool.HasComponent(*this, componentId));
		}

		void Entity::RemoveAllComponents( void )
		{
			world._entityAttributes._componentPool.RemoveAllEntityComponents(*this);
		}

		void Entity::RemoveComponent( TypeId componentTypeId )
		{
			world._entityAttributes._componentPool.RemoveComponent(*this, componentTypeId);
		}

		Component& Entity::GetComponent( TypeId componentTypeId ) const
		{
			return (world._entityAttributes._componentPool.GetComponent(*this, componentTypeId));
		}
	}
}
