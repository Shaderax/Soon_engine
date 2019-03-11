#pragma once

#include "Component.hpp"
#include "Config.hpp"
#include "Id.hpp"

#include <iostream>
#include <array>
#include <bitset>
#include <vector>

using namespace Soon::ECS;

namespace Soon
{
	namespace ECS
	{
		class ComponentPool
		{
			public:
				ComponentPool( std::size_t poolSize );
				~ComponentPool( void );

				void Resize( std::size_t amount );

				void AddComponent( Id idClass, Component* component, TypeId componentId );
				void RemoveComponent( Id id, TypeId componentId );

				Component& GetComponent( Id id, TypeId componentTypeId);

				void Clear( void );

				std::array< Component*, Soon::ECS::MAX_COMPONENTS >& GetEntityComponents( Id idClass );
				bool HasComponent( Id id, TypeId componentId );

				std::bitset<Soon::ECS::MAX_COMPONENTS>& GetComponentTypeList( Id id );

				void RemoveAllEntityComponents( Id id );

			private:
				struct EntityComponents
				{
					std::array< Component*, Soon::ECS::MAX_COMPONENTS > _entityComponents;
					std::bitset<Soon::ECS::MAX_COMPONENTS> _componentsTypeList;
				};

				std::vector<EntityComponents> _entitiesComponents;
		};
	}
}
