#pragma once

#include "Id.hpp"

#include <iostream>
#include <vector>

namespace Soon
{
	namespace ECS
	{
		class EntityPool
		{
			public:
				EntityPool( std::uint32_t poolSize );

				~EntityPool( void );

				Id		CreateEntity( void );
				std::size_t	GetEntityCount( void ) const;
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
