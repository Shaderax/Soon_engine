#include "Entity.hpp"
#include "World.hpp"
#include "System.hpp"
#include "Transform.hpp"

using namespace Soon::ECS;

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
	World world;

	Soon::ECS::Entity entite = world.CreateEntity();

	 //entite.AddComponent<Component>();
	// entite.AddComponent<Transform>();

	//world.AddSystem<Movement>();

	//	world::Update();

	//	world::GetSystem<Movement>().Update();

	return (0);
}
