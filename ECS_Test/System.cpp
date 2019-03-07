#include "System.hpp"
#include "Id.hpp"
#include <iostream>

namespace Soon
{
	namespace ECS
	{
		System::System( void )
		{

		}
		
		System::~System( void )
		{

		}
		bool System::PassFilters( std::bitset<Soon::ECS::MAX_COMPONENTS>& bitset ) const
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

		void System::AddEntity( Id id )
		{
			_entities.push_back(id);
		}

		std::vector< Id >& System::GetEntities( void )
		{
			return (_entities);
		}
	}
}
