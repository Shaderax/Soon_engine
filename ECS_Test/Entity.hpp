#pragma once

namespace Soon
{
	namespace ECS
	{
		class Entity
		{
			public:
				Entity( void );
				~Entity( void );

			private:
				std::uint64_t	id;
				World* _world;
		};
	}
}
