#pragma once
nanespace Soon
{
	namespace ECS
	{
		class EntityAttributes
		{
			EntityAttributes( void );
			~EntityAttributes( void );

			void Resize( std::size_t amount );
			struct Attribute
			{
				bool _activated;

				std::vector<bool> _systems;
			};
			private:
			ComponentPool _componentPool;

			std::vector<Attribute> _attributes;
		};

	}
}
