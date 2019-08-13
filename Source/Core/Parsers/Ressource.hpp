#pragma once

#include "ECS/ClassTypeId.hpp"

namespace Soon
{
	template<class T>
		class Resource
		{
			std::vector<T> GetData( void )
			{
				return (_data);
			}

			std::vector<T> _data;
		};
}
