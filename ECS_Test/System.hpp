#pragma once

namespace Soon
{

	namespace ECS
	{
		class System
		{
			public:
				System( void );
				virtual ~System( void );

				bool PassFilters( std::bitset& bitset ) const;
				void AddEntity( Entity::Id id );

			private:
				std::vector< Entity::Id >				_entities;
				std::bitset<Soon::ECS::MAX_COMPONENTS>	_requireComponents;
				std::bitset<Soon::ECS::MAX_COMPONENTS>	_excludeComponents;
		};

		template < T >
			std::uint32_t GetSystemTypeId( void ) const
			{
				return (ClassTypeId<System>::GetId<T>());
			}
	}
}
