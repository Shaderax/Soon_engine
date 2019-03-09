#pragma once

#include <cstdint>

namespace Soon
{
	namespace ECS
	{
		typedef std::uint32_t TypeId;

		struct Id
		{
			Id( TypeId id )
			{
				_id = id;
			};

			Id( void ) :
				_id(0)
			{
			};

			TypeId GetId( void ) { return (_id); };

			bool operator==( const Id& rhs )
			{
				return (_id == rhs._id);
			}

			bool operator!=( const Id& rhs )
			{
				return (!(_id == rhs._id));
			}

			void Clear( void )
			{
				_id = 0;
			}

			TypeId _id;
		};
	}
}
