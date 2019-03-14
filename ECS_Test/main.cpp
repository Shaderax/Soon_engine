#include "Entity.hpp"
#include "World.hpp"
#include "System.hpp"
#include "Transform.hpp"

using namespace Soon::ECS;

//class Movement : public System
//{
//	public:
//		Movement( void ) {};
//	void Update()
//	{
//		std::vector< Id >& entities = GetEntities();
//		for (auto entity : entities)
//		{
//
//		}
//	}
//};

int main()
{
	Entity entite;
	Entity entite2;

	std::cout << entite.GetId() << std::endl;
	std::cout << entite2.GetId() << std::endl;
//	entite.AddComponent<Transform>();

//	world.AddSystem<Movement>();
//
//	world.Update();
//
//	world.GetSystem<Movement>().Update();

	return (0);
}
