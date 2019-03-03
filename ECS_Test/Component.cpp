#include "Component.hpp"

namespace Soon
{
	namespace ECS
	{
		Component::Component( void )
		{

		}

		template < typename T >
		std::uint32_t GetComponentTypeId( void )
		{
			return (ClassTypeId::<Component>::GetId<T>());
		}

	}


}
