#pragma once

#include "Id.hpp"

using namespace Soon::ECS;

namespace Soon
{
	namespace ECS
	{
		class Component
		{
			public:
				Component( void );
				virtual ~Component( void );
		};

		template < typename T >
			TypeId GetComponentTypeId( void );
	}
}
