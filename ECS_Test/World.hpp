#pragma once

namespace Soon
{
	namespace ECS
	{
		class World
		{
			public:
				World( void );
				~World( void );

			private:
				std::vector<Entity>	_entityArray;
		}

	}


}
