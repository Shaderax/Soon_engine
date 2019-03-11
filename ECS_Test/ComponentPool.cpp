#include "ComponentPool.hpp"
#include "Component.hpp"
#include "Config.hpp"
#include "Id.hpp"

#include <iostream>
#include <array>

using namespace Soon::ECS;

namespace Soon
{
	namespace ECS
	{
		ComponentPool::ComponentPool( std::size_t poolSize ) :
			_entitiesComponents( poolSize )
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

		void ComponentPool::RemoveComponent( Id id, TypeId componentId )
		{
			TypeId index = id.GetId();
			_entitiesComponents[index]._entityComponents[componentId] = nullptr;
			_entitiesComponents[index]._componentsTypeList[componentId] = false;
		}

		void ComponentPool::RemoveAllEntityComponents( Id id )
		{
			TypeId index = id.GetId();
			EntityComponents& entityComponents = _entitiesComponents[index];

			for(auto& c : entityComponents._entityComponents)
				delete c;
			entityComponents._componentsTypeList.reset();
		}

		std::array< Component*, Soon::ECS::MAX_COMPONENTS >& ComponentPool::GetEntityComponents( Id idClass )
		{
			return (_entitiesComponents[idClass.GetId()]._entityComponents);
		}

		std::bitset<Soon::ECS::MAX_COMPONENTS>& ComponentPool::GetComponentTypeList( Id id )
		{
			return (_entitiesComponents[id.GetId()]._componentsTypeList);
		}

		bool ComponentPool::HasComponent( Id id, TypeId componentId )
		{
			std::array< Component*, Soon::ECS::MAX_COMPONENTS >& components = GetEntityComponents(id);

			return (components[componentId] != nullptr);
		}

		void ComponentPool::Clear( void )
		{
			_entitiesComponents.clear();
		}

		Component& ComponentPool::GetComponent( Id id, TypeId componentTypeId )
		{
			return *(GetEntityComponents( id )[componentTypeId]);
		}
	}
}
