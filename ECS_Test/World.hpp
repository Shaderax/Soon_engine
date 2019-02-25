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

				Entity CreateEntity( void );
				EntityPool GetEntityPool( void );
				void Update( void );

			private:
				EntityPool		_entityPool;
				ComponentPool	_componentPool;
				SystemPool		_systemPool;
				EntityCache		_entityCache;
		};

	}


}
