#pragma once

#include "Id.hpp"
#include "Config.hpp"
#include "Entity.hpp"
#include "System.hpp"
#include "EntityPool.hpp"
#include "EntityCache.hpp"
#include "EntityAttributes.hpp"

#include <iostream>
#include <unordered_map>
#include <memory>

using namespace Soon::ECS;

namespace Soon
{
	namespace ECS
	{
		class Entity;

		class World
		{
			public:
				//				World( void );
				~World( void );

				Entity		CreateEntity( void );
				Id 			CreateEntityId( void );
				std::vector<Entity> CreateEntities(std::size_t amount);
				EntityPool	GetEntityPool( void );
				void		Update( void );
				void		CheckResizePool( std::size_t amount );
				void		Resize( std::size_t amount );
				std::size_t	GetAliveEntityCount( void ) const;
				std::size_t	GetEntityCount( void ) const;

				void ActivateEntity( Entity entity );
				void DesactivateEntity( Entity entity );

				void RemoveAllSystems( void );
				void RemoveSystem( TypeId SystemTypeId );

				bool	IsActivated( Entity entity );
				void	KillEntity( Entity entity );
				void	KillEntities(std::vector<Entity>& entities);

				void	Clear( void );

				void AddSystem( System* sys, TypeId SystemTypeId );

				template < typename T >
					void AddSystem( void );

				template < typename T >
					void RemoveSystem( void );

				template < typename T >
					T& GetSystem( void );

				bool IsValid( Entity entity ) const;

				static World& GetInstanceWorld( void )
				{
					std::cout << "NONONONO" << std::endl;
					static World world;
					return (world);
				}

				template < typename T >
					bool HasSystem( void ) const;
				bool HasSystem( TypeId idSys ) const;

			private:
				World( std::uint32_t poolSize = Soon::ECS::DEFAULT_POOL_SIZE );
				EntityPool			_entityPool;
				EntityCache			_entityCache;
				EntityAttributes	_entityAttributes;

				std::unordered_map<TypeId, System*> _systemPool;

				friend class Entity;
		};

		template < class T >
			void World::AddSystem( void )
			{
				static_assert(std::is_base_of<System, T>(), "Template argument does not inherit from System");
				ECS_ASSERT(!HasSystem<T>(), "System argument is already in World");
				T* newSystem = new T();

				AddSystem(newSystem, GetSystemTypeId<T>());
			}

		template < class T >
			void World::RemoveSystem( void )
			{
				static_assert(std::is_base_of<System, T>(), "Template argument does not inherit from System");
				static_assert(HasSystem<T>(), "System argument is not in World");
				RemoveSystem(GetSystemTypeId<T>());
			}

		template < typename T >
			T& World::GetSystem( void )
			{
				static_assert(std::is_base_of<System, T>(), "Template argument does not inherit from System");
				return *(static_cast<T*>(_systemPool[GetSystemTypeId<T>()]));
			}

		template < typename T >
			bool World::HasSystem( void ) const
			{
				return (HasSystem(GetSystemTypeId<T>()));
			}
	}
}
