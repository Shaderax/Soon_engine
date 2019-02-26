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

			private:
				EntityPool		_entityPool;
				ComponentPool	_componentPool;
				SystemPool		_systemPool;
				EntityCache		_entityCache;
		};

	}


}
