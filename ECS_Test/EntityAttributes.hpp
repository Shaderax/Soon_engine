#pragma once

#include "ComponentPool.hpp"

#include <iostream>
#include <vector>

using namespace Soon::ECS;

namespace Soon
{
	namespace ECS
	{
		struct EntityAttributes
		{
			EntityAttributes( std::uint32_t poolSize );

			void Resize( std::size_t amount );

			struct Attribute
			{
				bool _activated;

				std::vector<bool> _systems;
			};

			ComponentPool _componentPool;

			std::vector<Attribute> _attributes;
		};

	}
}
