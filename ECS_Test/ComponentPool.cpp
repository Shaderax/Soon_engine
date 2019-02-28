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

		void addComponent( Entity::Id idClass, Component* component, std::uint32_t componentId )
		{
			std::uint32_t index = idClass.GetId();
			GetEntityComponents( index )._entityComponents[componentId] = component;
		}

		void GetEntityComponents( std::uint32_t id )
		{
			return (_entitiesComponents[id]);
		}
	}
}
