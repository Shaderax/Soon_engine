#include "World.hpp"
#include "System.hpp"
#include "Entity.hpp"

using namespace Soon::ECS;

struct Position : Component
{
	Position( float x, float y ) : _x(x), _y(x)
	{

	}
	float _x;
	float _y;
};

struct TransformComponent : Component
{
	    int transform;
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
	World world;

	Soon::ECS::Entity entite = world.CreateEntity();

	entite.AddComponent<TransformComponent>();

	//	world.AddSystem<Movement>();

	//	world::Update();

	//	world::GetSystem<Movement>().Update();

	return (0);
}
