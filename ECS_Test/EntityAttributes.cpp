#include "EntityAttributes.hpp"

namespace Soon
{
	namespace ECS
	{
		void EntityAttributes::Resize( std::size_t amount )
		{
			_componentPool.Resize(amount);
			_attributes.resize(amount);
		}
	}
}
