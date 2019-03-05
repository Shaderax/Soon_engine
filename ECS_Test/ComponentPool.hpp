#pragma once

#include "Entity.hpp"
#include <iostream>
#include "Config.hpp"
#include <array>

using namespace Soon::ECS;

namespace Soon
{
	namespace ECS
	{
		class ComponentPool
		{
			public:
				ComponentPool( void );
				~ComponentPool( void );

				void Resize( std::size_t amount );

				template < typename T >
				void addComponent( Entity::Id idClass, T component, std::uint32_t componentId );

				void GetEntityComponents( Entity::Id idClass );
				bool HasComponent( Entity::Id id, std::uint32_t componentId );

				std::bitset<Soon::ECS::MAX_COMPONENTS>& GetComponentTypeList( Entity::Id id );

			private:
				class EntityComponents
				{
					private:
						std::array< Component*, Soon::ECS::MAX_COMPONENTS > _entityComponents;
						std::bitset<Soon::ECS::MAX_COMPONENTS> _componentTypeList;
				};

				std::vector<EntityComponents> _entitiesComponents;
		};
	}
}
