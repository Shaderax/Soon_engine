#include "ComponentPool.hpp"
#include "Component.hpp"
#include "Entity.hpp"
#include "Config.hpp"
#include "Id.hpp"

#include <iostream>
#include <array>

using namespace Soon::ECS;

namespace Soon
{
	namespace ECS
	{
		ComponentPool::ComponentPool( void )
		{

		}

		ComponentPool::~ComponentPool( void )
		{

		}

		void ComponentPool::Resize( std::size_t amount )
		{
			_entitiesComponents.resize(amount);
		}

		void ComponentPool::AddComponent( Id idClass, Component* component, TypeId componentId )
		{
			TypeId index = idClass.GetId();
			_entitiesComponents[index]._entityComponents[componentId] = component;
			_entitiesComponents[index]._componentsTypeList[componentId] = true;
		}

		std::array< Component*, Soon::ECS::MAX_COMPONENTS >& ComponentPool::GetEntityComponents( Id idClass )
		{
			return (_entitiesComponents[idClass.GetId()]._entityComponents);
		}

		bool ComponentPool::HasComponent( Id id, TypeId componentId ) const
		{
			std::array< Component*, Soon::ECS::MAX_COMPONENTS >& components = GetEntityComponents(id);

			return (components[componentId] != nullptr);
		}

		std::bitset<Soon::ECS::MAX_COMPONENTS>& ComponentPool::GetComponentTypeList( Id id )
		{
			return (_entitiesComponents[id.GetId()]._componentsTypeList);
		}
	}
}
