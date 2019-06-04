#pragma once

#include "Component.hpp"
#include "Config.hpp"
#include "Id.hpp"

using namespace Soon::ECS;

namespace Soon
{
	namespace ECS
	{
		class World;

		class Entity
		{
			public:
				Entity( void );
				Entity( TypeId id );
				~Entity( void );

				TypeId GetId( void ) const;

				Id GetIdClass( void ) const;

				bool IsValid( void ) const;

				bool IsActivated( void ) const;
				void Activate( void );
				void Desactivate( void );
				void Kill( void );

				void RemoveAllComponents( void );

				template < typename T, typename ... Args >
					T& AddComponent( Args && ... args );

				void AddComponent( Component* component, TypeId componentId);

				template <typename T>
					bool HasComponent( void ) const;

				bool HasComponent( TypeId componentId ) const;

				template < typename T >
					void RemoveComponent( void );

				void RemoveComponent( TypeId componentTypeId );

				template < typename T >
					T& GetComponent( void ) const;

				Component& GetComponent( TypeId componentTypeId ) const;

				bool operator==( const Entity& rhs )
				{
					return (_id == rhs._id);
				}

			private:
				Id _id;
		};

		template < typename T, typename ... Args >
			T& Entity::AddComponent( Args && ... args )
			{
				static_assert(std::is_base_of<Component, T>(), "T is not a component, cannot add T");
	//			std::cout << "In Add Component : " << GetId() << std::endl;
				T* component = new T(*this, std::forward<Args>(args) ...);
				AddComponent(component, GetComponentTypeId<T>());
				Activate();
				return *(component);
			}

		template <typename T>
			bool Entity::HasComponent( void ) const
			{
				static_assert(std::is_base_of<Component, T>(), "T is not a component, HasComponent");
				return (HasComponent(GetComponentTypeId<T>()));
			}

		template < typename T >
			void Entity::RemoveComponent( void )
			{
				static_assert(std::is_base_of<Component, T>(), "T is not a component, cannot remove T");
				Activate();
				RemoveComponent(GetComponentTypeId<T>());
			}

		template < typename T >
			T& Entity::GetComponent( void ) const
			{
				static_assert(std::is_base_of<Component, T>(), "T is not a component, cannot get T");
				return (static_cast<T&>(GetComponent(GetComponentTypeId<T>())));
			}
	}
}
