#pragma once
nanespace Soon
{
	namespace ECS
	{
		class EntityAttributes
		{
			public:
				EntityAttributes( void );
				~EntityAttributes( void );

				void Resize( std::size_t amount );

				struct Attribute
				{
					bool _activated;

					std::vector<bool> _systems;
				};

				ComponentPool _componentPool;

				std::vector<Attribute> _attributes;
		};

	}
}
