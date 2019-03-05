#pragma once

#include <iostream>

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
			std::uint32_t GetComponentTypeId( void );
	}
}
