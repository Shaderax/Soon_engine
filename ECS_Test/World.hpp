#pragma once

#include "Id.hpp"
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
				World( void );
				World( std::uint32_t poolSize );
				~World( void );

				Entity		CreateEntity( void );
				std::vector<Entity> CreateEntities(std::size_t amount);
				EntityPool	GetEntityPool( void );
				void		Update( void );
				void		CheckResizePool( std::size_t amount );
				void		Resize( std::size_t amount );
				std::size_t	GetAliveEntityCount( void ) const;
				std::size_t	GetEntityCount( void ) const;

				void ActivateEntity( Id id );
				void DesactivateEntity( Id id );

				void RemoveAllSystems( void );
				void RemoveSystem( TypeId SystemTypeId );

				bool	IsActivated( Id id );
				void	KillEntity( Id id );
				void	KillEntities(std::vector<Entity>& entities);

				void	Clear( void );

				void AddSystem( System* sys, TypeId SystemTypeId );

				template < typename T >
					void AddSystem( void );

				template < typename T >
					void RemoveSystem( void );

				template < typename T >
					T& GetSystem( void );

				bool IsValid( Id id ) const;

			private:
				EntityPool			_entityPool;
				EntityCache			_entityCache;
				EntityAttributes	_entityAttributes;

				std::unordered_map<TypeId, System*> _systemPool;

				friend class Entity;
		};

		template < class T >
			void World::AddSystem( void )
			{
				T* newSystem = new T();

				AddSystem(newSystem, GetSystemTypeId<T>());
			}

		template < class T >
			void World::RemoveSystem( void )
			{
				RemoveSystem(GetSystemTypeId<T>());
			}

		template < typename T >
			T& World::GetSystem( void )
			{
				return *(static_cast<T*>(_systemPool[GetSystemTypeId<T>()]));
			}
	}
}
