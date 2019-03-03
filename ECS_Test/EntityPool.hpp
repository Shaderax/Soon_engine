#pragma once

#include "Entity.hpp"

namespace Soon
{
	namespace ECS
	{
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
				std::uint32_t		_nextId;
				std::vector<Entity::Id>	_freeId;
				std::vector<bool>	_idKilled;
		};
	}
}
