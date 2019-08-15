#pragma once

#include "ECS/ClassTypeId.hpp"

namespace Soon
{
	template<class T>
		class Resource
		{
			T GetData( void )
			{
				return (_data);
			}

			T _data;
		};
}
