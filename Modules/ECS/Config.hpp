#pragma once

#include <iostream>
#include <cassert>

namespace Soon
{
	namespace ECS
	{
		constexpr const std::uint32_t MAX_COMPONENTS = 64;
		constexpr const std::uint32_t DEFAULT_POOL_SIZE = 64;
	}
}

#define ECS_ASSERT(condition, failMessage) assert((condition) && failMessage)
