#pragma once

#include "Entity.hpp"
#include "Config.hpp"
#include "ClassTypeId.hpp"
#include "Component.hpp"

using namespace Soon::ECS;

namespace Soon
{
	namespace ECS
	{
		class Entity;

		class System
		{
			public:
				System( void );
				virtual ~System( void );

				bool PassFilters( std::bitset<Soon::ECS::MAX_COMPONENTS>& bitset ) const;
				void AddEntity( Entity::Id id );

				std::vector< Entity::Id > GetEntities( void );

			private:
				std::vector< Entity::Id >				_entities;
				std::bitset<Soon::ECS::MAX_COMPONENTS>	_requireComponents;
				std::bitset<Soon::ECS::MAX_COMPONENTS>	_excludeComponents;
		};

		template < typename T >
			std::uint32_t GetSystemTypeId( void )
			{
				return (ClassTypeId<System>::GetId<T>());
			}
	}
}
