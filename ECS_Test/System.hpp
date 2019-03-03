#pragma once

namespace Soon
{

	namespace ECS
	{
		class System
		{
			System( void );
			virtual ~System( void );

		};

		template < T >
		std::uint32_t GetSystemTypeId( void ) const
		{
			return (ClassTypeId<System>::GetId<T>());
		}
	}
}
