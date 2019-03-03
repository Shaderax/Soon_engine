#include "ComponentPool.hpp"
#include "Entity.hpp"

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

		void ComponentPool::addComponent( Entity::Id idClass, Component* component, std::uint32_t componentId )
		{
			std::uint32_t index = idClass.GetId();
			GetEntityComponents( index )._entityComponents[componentId] = component;
		}

		EntityComponents& ComponentPool::GetEntityComponents( std::uint32_t id ) const
		{
			return (_entitiesComponents[id]);
		}

		bool ComponentPool::HasComponent( Entity:: id, std::uint32_t componentId ) const
		{
			EntityComponents& components = GetEntityComponents(id.GetId());

			return (components[componentId] != nullptr)
		}
	}
}
