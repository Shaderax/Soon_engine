#pragma once

#include "Entity.hpp"
#include <iostream>
#include <vector>

namespace Soon
{
	namespace ECS
	{
		class Entity;
		class Entity::Id;

		class EntityPool
		{
			public:
				EntityPool( std::size_t poolSize ) { _nextId = 0; };
				~EntityPool( void );

				Entity		CreateEntity( void );
				std::size_t	GetEntityCount( void );
				void		Resize( std::size_t amount );
				void		Remove( Entity::Id id );

			private:
				std::uint32_t			_nextId;
				std::vector< Entity::Id >	_freeId;
				std::vector< bool >		_idKilled;
		};
	}
}
