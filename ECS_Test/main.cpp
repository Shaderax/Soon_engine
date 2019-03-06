#include "Id.hpp"
#include "World.hpp"
#include "EntityPool.hpp"
#include "Entity.hpp"
#include "Component.hpp"
#include "System.hpp"

using namespace Soon::ECS;

class Position : Component
{
	float x;
	float y;
};

class Movement : System
{
	void Update()
	{
		std::vector< Id >& entities = GetEntities();
		for (auto entity : entities)
		{
			
		}
	}
};

int main(int argc, char **argv)
{
	Soon::ECS::World world;

//	Soon::ECS::Entity entite = world.CreateEntity();
//
//	entite.AddComponent<Position>(5, 5);
//
//	world.AddSystem<Movement>();
//
//	world::Update();
//
//	world::GetSystem<Movement>().Update();

	return (0);
}
