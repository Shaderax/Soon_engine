#include "Entity.hpp"
#include "World.hpp"
#include "System.hpp"
#include "Transform.hpp"

using namespace Soon::ECS;

class Movement : public System
{
	public:
		Movement( void ) {};
	void Update()
	{
		std::vector< Entity >& entities = GetEntities();
		for (auto& entity : entities)
		{
			entity.GetComponent<Transform>().x += 1.0001f;
		}
	}
};

int main()
{
	Entity entite;
	Entity entite2;

	std::cout << entite.GetId() << std::endl;
	std::cout << entite2.GetId() << std::endl;
	entite.AddComponent<Transform>();
	Transform& iho = entite.GetComponent<Transform>();

	iho.x = 10.0f;
	std::cout << entite.GetComponent<Transform>().x << std::endl;

	world.AddSystem<Movement>();
	entite.Activate();

	world.Update();

	world.GetSystem<Movement>().Update();

	std::cout << entite.GetComponent<Transform>().x << std::endl;

	return (0);
}
