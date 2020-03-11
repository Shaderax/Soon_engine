#include "World.hpp"
#include "Entity.hpp"
#include "Id.hpp"
#include "Component.hpp"
#include "Config.hpp"

#include <iostream>

namespace Soon
{
	namespace ECS
	{
		Entity::Entity( void ) :
			_id(Soon::ECS::World::GetInstance().CreateEntityId())
		{
			Activate();
		}

		Entity::Entity( TypeId id ) :
			_id(id)
		{
		}

		Entity::~Entity( void )
		{
//			Kill();
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
			return (Soon::ECS::World::GetInstance().IsActivated(*this));
		}

		void Entity::Activate( void )
		{
			Soon::ECS::World::GetInstance().ActivateEntity(*this);
		}

		void Entity::Deactivate( void )
		{
			Soon::ECS::World::GetInstance().DeactivateEntity(*this);
		}

		void Entity::Kill( void )
		{
			Soon::ECS::World::GetInstance().KillEntity(*this);
		}

		// Maybe Set To Private
		void Entity::AddComponent( Component* component, TypeId componentId )
		{
			Soon::ECS::World::GetInstance()._entityAttributes._componentPool.AddComponent(*this, component, componentId);
		}

		bool Entity::IsValid( void ) const
		{
			return (Soon::ECS::World::GetInstance().IsValid(*this));
		}

		bool Entity::HasComponent( TypeId componentId ) const
		{
			return (Soon::ECS::World::GetInstance()._entityAttributes._componentPool.HasComponent(*this, componentId));
		}

		void Entity::RemoveAllComponents( void )
		{
			Soon::ECS::World::GetInstance()._entityAttributes._componentPool.RemoveAllEntityComponents(*this);
		}

		void Entity::RemoveComponent( TypeId componentTypeId )
		{
			Soon::ECS::World::GetInstance()._entityAttributes._componentPool.RemoveComponent(*this, componentTypeId);
		}

		Component& Entity::GetComponent( TypeId componentTypeId ) const
		{
			return (Soon::ECS::World::GetInstance()._entityAttributes._componentPool.GetComponent(*this, componentTypeId));
		}

		void Entity::EnableComponent( TypeId componentTypeId )
		{
			Soon::ECS::World::GetInstance()._entityAttributes._componentPool.EnableComponent(*this, componentTypeId);
		}

		void Entity::DisableComponent( TypeId componentTypeId )
		{
			Soon::ECS::World::GetInstance()._entityAttributes._componentPool.DisableComponent(*this, componentTypeId);
		}

		bool Entity::IsComponentActivated( TypeId componentTypeId )
		{
			return (Soon::ECS::World::GetInstance()._entityAttributes._componentPool.IsComponentActivated(*this, componentTypeId));
		}
	}
}
