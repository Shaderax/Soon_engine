#pragma once

#include "Config.hpp"
#include "Id.hpp"
#include "ClassTypeId.hpp"

#include <bitset>
#include <vector>

using namespace Soon::ECS;

namespace Soon
{
	namespace ECS
	{
		class System
		{
			public:
				System( void );
				virtual ~System( void );

				bool PassFilters( std::bitset<Soon::ECS::MAX_COMPONENTS>& bitset ) const;
				void AddEntity( Id id );
				void RemoveEntity( Id id );

				std::vector< Id >& GetEntities( void );

			private:
				std::vector< Id >						_entities;
				std::bitset<Soon::ECS::MAX_COMPONENTS>	_requireComponents;
				std::bitset<Soon::ECS::MAX_COMPONENTS>	_excludeComponents;
		};

		template < typename T >
			TypeId GetSystemTypeId( void )
			{
				return (ClassTypeId<System>::GetId<T>());
			}
	}
}
