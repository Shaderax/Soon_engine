#pragma once

#include "Config.hpp"
#include "Id.hpp"
#include "ClassTypeId.hpp"
#include "Component.hpp"

#include <bitset>
#include <vector>

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
				virtual void Update( void );

				bool PassFilters( std::bitset<Soon::ECS::MAX_COMPONENTS>& bitset ) const;
				void AddEntity( Entity entity );
				void RemoveEntity( Entity entity );

				template <typename T>
					void RequireComponent( void );

				std::vector< Entity >& GetEntities( void );

			private:
				std::vector< Entity >				_entities;
				std::bitset<Soon::ECS::MAX_COMPONENTS>	_requireComponents;
				std::bitset<Soon::ECS::MAX_COMPONENTS>	_excludeComponents;
		};

		template < typename T >
			TypeId GetSystemTypeId( void )
			{
				return (ClassTypeId<System>::GetId<T>());
			}

		template <typename T>
			void System::RequireComponent( void )
			{
				static_assert(std::is_base_of<Component, T>(), "T is not a component, cannot add T");
				_requireComponents.set(GetComponentTypeId<T>());
			}

	}
}
