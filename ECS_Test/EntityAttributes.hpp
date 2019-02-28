#pragma once
nanespace Soon
{
	namespace ECS
	{
		class EntityAttributes
		{
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
