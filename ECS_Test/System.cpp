#include "System.hpp"

namespace Soon
{
	namespace ECS
	{
		bool System::PassFilters( std::bitset& bitset ) const
		{
			for(std::size_t i = 0; i < _requireComponents.size(); ++i)
			{
				if(_requireComponents[i] == true && bitset[i] == false)
				{
					return false;
				}
			}

			if((_excludeComponents & bitset).any())
				return false;

			return (true);
		}

		void System::AddEntity( Entity::Id id )
		{
			_entities.push_back(id);
		}

		std::vector< Entity::Id > GetEntities(void ) const
		{
			return (_entities);
		}
	}
}
