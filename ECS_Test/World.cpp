#include "World.hpp"

namespace Soon
{
	namespace ECS
	{
		Entity World::CreateEntity( void )
		{
			GetEntityPool().CreateEntity();
		}

		EntityPool World::GetEntityPool( void )
		{

		}
	}
}
