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

		template < typename T, Args && ... args >
			void Entity::AddComponent( Args && ... args )
			{
				T* component = new T{std::forward<Args>(args)...};
				addComponent(component, GetComponentTypeId<T>());
			}

		template < typename T >
			void Entity::AddComponent( T* component, std::uint32_t componentId)
			{
				GetWorld()._entityAttributes._componentPool.addComponent(GetIdClass(), component, componentId);
			}

		bool Entity::IsValid( void ) const
		{
			return (GetWorld().IsValid(GetIdClass()));
		}

		template <typename T>
			bool Entity::HasComponent() const
			{
				return (HasComponent(GetComponentTypeId<T>()));
			}

		template < typename T >
			bool Entity::HasComponent( std::uint32_t componentId ) const
			{
				GetWorld()._entitiesAttributes._componentPool.HasComponent(GetIdClass(), componentId);
			}
	}
}
