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

			//	EntityComponentStorage componentStorage;

			std::vector<Attribute> _attributes;
		};

	}
}
