#include "World.hpp"
#include "EntityPool.hpp"
#include "Entity.hpp"

int main(int argc, char **argv)
{
	Soon::ECS::World world;

	Soon::ECS::Entity entite = world.CreateEntity();

	entite.AddComponent<Position>();

	return (0);
}
