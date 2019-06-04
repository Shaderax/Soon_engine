#include "System.hpp"
#include "Id.hpp"
#include "Entity.hpp"

#include <iostream>
#include <algorithm>

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

		void System::Update( void )
		{

		}

		bool System::PassFilters( std::bitset<Soon::ECS::MAX_COMPONENTS>& bitset ) const
		{
			for (std::size_t i = 0; i < _requireComponents.size(); ++i)
			{
				if (_requireComponents[i] == true && bitset[i] == false)
					return false;
			}

			if ((_excludeComponents & bitset).any())
				return false;

			return (true);
		}

		void System::AddEntity( Entity entity )
		{
			_entities.push_back(entity);
		}

		void System::RemoveEntity( Entity entity )
		{
			_entities.erase(std::remove(_entities.begin(), _entities.end(), entity), _entities.end());
		}

		std::vector< Entity >& System::GetEntities( void )
		{
			return (_entities);
		}
	}
}
