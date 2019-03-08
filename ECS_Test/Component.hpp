#pragma once

#include "Id.hpp"
#include "ClassTypeId.hpp"

using namespace Soon::ECS;

namespace Soon
{
	namespace ECS
	{
		class Component
		{
			public:
				virtual ~Component( void ) {};
		};

		template < typename T >
			TypeId GetComponentTypeId( void )
			{
				return (ClassTypeId<Component>::GetId<T>());
			}
	}
}
