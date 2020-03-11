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
		class Entity;

		class ComponentPool
		{
			public:
				ComponentPool( std::size_t poolSize );
				~ComponentPool( void );

				void Resize( std::size_t amount );

				void AddComponent( Entity entity, Component* component, TypeId componentId );
				void RemoveComponent( Entity entity, TypeId componentId );

				void EnableComponent( Entity entity, TypeId componentId );
				void DisableComponent( Entity entity, TypeId componentId );

				bool IsComponentActivated( Entity entity, TypeId componentId );

				Component& GetComponent( Entity entity, TypeId componentTypeId);

				void Clear( void );

				std::array< Component*, Soon::ECS::MAX_COMPONENTS >& GetEntityComponents( Entity entity );
				bool HasComponent( Entity entity, TypeId componentId );

				std::bitset<Soon::ECS::MAX_COMPONENTS>& GetComponentTypeList( Entity entity );

				void RemoveAllEntityComponents( Entity entity );

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
