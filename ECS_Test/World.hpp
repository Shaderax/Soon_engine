#pragma once

#include "Entity.hpp"
#include "EntityPool.hpp"

namespace Soon
{
	namespace ECS
	{
		class World
		{
			public:
				World( void );
				~World( void );

				Entity		CreateEntity( void );
				EntityPool	GetEntityPool( void );
				void		Update( void );
				void		Resize( std::size_t amount );
				void		CheckResizePool( std::size_t amount );
				std::size_t	GetAliveEntityCount( void ) const;
				std::size_t	GetEntityCount( void ) const;

				bool	IsActivated( Entity::Id id );
				void	KillEntity( Entity::Id id );

				template < typename T >
				void AddSystem( void );

			private:
				EntityPool			_entityPool;
				EntityCache			_entityCache;
				EntityAttributes	_entityAttributes;

				std::unordered_map<std::uint32_t, System> _systemPool;
		};

	}
}
