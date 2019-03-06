#include "Component.hpp"
#include "ClassTypeId.hpp"
#include "Id.hpp"
#include <cstdint>

using namespace Soon::ECS;

namespace Soon
{
	namespace ECS
	{
		Component::Component( void )
		{

		}

		template < typename T >
			TypeId GetComponentTypeId( void )
			{
				return (ClassTypeId<Component>::GetId<T>());
			}

	}
}
