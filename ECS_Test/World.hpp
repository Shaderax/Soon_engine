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
				EntityPool	GetEntityPool( void );
				void		Update( void );
				void		Resize( std::size_t amount );
				void		CheckResizePool( std::size_t amount );
				std::size_t	GetAliveEntityCount( void ) const;
				std::size_t	GetEntityCount( void ) const;

				void ActivateEntity( Id id );
				void DesactivateEntity( Id id );

				bool	IsActivated( Id id );
				void	KillEntity( Id id );

				template < typename T >
					void AddSystem( void );

				template < typename T >
					T& GetSystem( void );

				bool IsValid( Id id );

			private:
				EntityPool			_entityPool;
				EntityCache			_entityCache;
				EntityAttributes	_entityAttributes;

				std::unordered_map<TypeId, std::shared_ptr<System>> _systemPool;

				friend class Entity;
		};

		template < typename T >
			void World::AddSystem( void )
			{
				T* newSystem = new T();
				TypeId idSystem = GetSystemTypeId<T>();

				_systemPool[idSystem] = newSystem;
			}

		template < typename T >
			T& World::GetSystem( void )
			{
				return *(std::static_pointer_cast<T>(_systemPool[GetSystemTypeId<T>()]));
			}
	}
}
