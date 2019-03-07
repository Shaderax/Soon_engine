#pragma once

#include <cstdint>

namespace Soon
{
	namespace ECS
	{
		typedef std::uint32_t TypeId;

		struct Id
		{
				Id( TypeId id ) { _id = id; };
				Id( void ) : _id(0) {};

				TypeId GetId( void ) { return (_id); };

				TypeId _id;
		};
	}
}
