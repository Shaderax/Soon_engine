#include "EntityAttributes.hpp"

namespace Soon
{
	namespace ECS
	{
		EntityAttributes::EntityAttributes( std::uint32_t poolSize ) :
			_componentPool( poolSize ),
			_attributes( poolSize )
		{

		}

		void EntityAttributes::Resize( std::size_t amount )
		{
			_componentPool.Resize(amount);
			_attributes.resize(amount);
		}

		void EntityAttributes::Clear( void )
		{
			_componentPool.Clear();
			_attributes.clear();
		}
	}
}
