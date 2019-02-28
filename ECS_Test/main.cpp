#include "World.hpp"
#include "EntityPool.hpp"
#include "Entity.hpp"

class Position : Soon::ECS::Component
{
	float x;
	float y;
};

int main(int argc, char **argv)
{
	Soon::ECS::World world;

	Soon::ECS::Entity entite = world.CreateEntity();

	entite.AddComponent<Position>(5, 5);

	return (0);
}
