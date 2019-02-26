#pragma once

#include "Entity.hpp"

namespace Soon
{
	namespace ECS
	{
		class EntityPool
		{
			public:
				EntityPool( World& world ) { _nextId = 0; };
				~EntityPool( void );

				Entity	CreateEntity( void );
				std::size_t GetEntityCount( void );
				void	Resize( std::size_t amount );

			private:
				std::uint32_t		_nextId;
				std::vector<Entity>	_freeId;
		};
	}
}
