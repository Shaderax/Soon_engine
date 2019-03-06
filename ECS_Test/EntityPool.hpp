#pragma once

#include "Entity.hpp"
#include "Id.hpp"

#include <iostream>
#include <vector>

namespace Soon
{
	namespace ECS
	{
		class Entity;

		class EntityPool
		{
			public:
				EntityPool( std::uint32_t poolSize )
			   	{
					_nextId = 0;
					Resize(poolSize);
			   	};

				~EntityPool( void );

				Entity		CreateEntity( void );
				std::size_t	GetEntityCount( void );
				void		Resize( std::size_t amount );
				void		Remove( Id id );

				bool		IsValid( Id id );

			private:
				TypeId					_nextId;
				std::vector< Id >	_freeId;
				std::vector< bool >		_idKilled;
		};
	}
}
