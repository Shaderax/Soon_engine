#include "ComponentPool.hpp"
#include "Component.hpp"
#include "Config.hpp"
#include "Id.hpp"
#include "Entity.hpp"

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

		void ComponentPool::EnableComponent( Entity entity, TypeId componentId )
		{
			ECS_ASSERT(entity.IsValid() && HasComponent(entity, componentId), "invalid entity cannot have components added to it");

			TypeId index = entity.GetId();
			_entitiesComponents[index]._componentsTypeList[componentId] = true;
		}

		bool ComponentPool::IsComponentActivated( Entity entity, TypeId componentId )
		{
			ECS_ASSERT(entity.IsValid() && HasComponent(entity, componentId), "invalid entity cannot have components added to it");

			TypeId index = entity.GetId();
			return (_entitiesComponents[index]._componentsTypeList[componentId]);
		}

		void ComponentPool::DisableComponent( Entity entity, TypeId componentId )
		{
			ECS_ASSERT(entity.IsValid() && HasComponent(entity, componentId), "invalid entity cannot remove components");

			TypeId index = entity.GetId();
			_entitiesComponents[index]._componentsTypeList[componentId] = false;
		}

		void ComponentPool::AddComponent( Entity entity, Component* component, TypeId componentId )
		{
			ECS_ASSERT(entity.IsValid(), "invalid entity cannot have components added to it");

			TypeId index = entity.GetId();
			_entitiesComponents[index]._entityComponents[componentId] = component;
			_entitiesComponents[index]._componentsTypeList[componentId] = true;
		}

		void ComponentPool::RemoveComponent( Entity entity, TypeId componentId )
		{
			ECS_ASSERT(entity.IsValid(), "invalid entity cannot remove components");
			TypeId index = entity.GetId();
			delete _entitiesComponents[index]._entityComponents[componentId];
			_entitiesComponents[index]._entityComponents[componentId] = nullptr;
			_entitiesComponents[index]._componentsTypeList[componentId] = false;
		}

		void ComponentPool::RemoveAllEntityComponents( Entity entity )
		{
			TypeId index = entity.GetId();
			EntityComponents& entityComponents = _entitiesComponents[index];

			for(auto& c : entityComponents._entityComponents)
				delete c;
			entityComponents._componentsTypeList.reset();
		}

		std::array< Component*, Soon::ECS::MAX_COMPONENTS >& ComponentPool::GetEntityComponents( Entity entity )
		{
			return (_entitiesComponents[entity.GetId()]._entityComponents);
		}

		std::bitset<Soon::ECS::MAX_COMPONENTS>& ComponentPool::GetComponentTypeList( Entity entity )
		{
			ECS_ASSERT(entity.IsValid(), "invalid entity cannot retrieve the component list");
			return (_entitiesComponents[entity.GetId()]._componentsTypeList);
		}

		bool ComponentPool::HasComponent( Entity entity, TypeId componentId )
		{
			std::array< Component*, Soon::ECS::MAX_COMPONENTS >& components = GetEntityComponents(entity);

			return (components[componentId] != nullptr);
		}

		void ComponentPool::Clear( void )
		{
			_entitiesComponents.clear();
		}

		Component& ComponentPool::GetComponent( Entity entity, TypeId componentTypeId )
		{
			ECS_ASSERT(entity.IsValid() && HasComponent(entity, componentTypeId), "Entity is not valid or does not contain component");
			return *(GetEntityComponents( entity )[componentTypeId]);
		}
	}
}
