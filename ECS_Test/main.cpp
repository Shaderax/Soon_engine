#include "Entity.hpp"
#include "World.hpp"
#include "System.hpp"
#include "Transform.hpp"

class Movement : public System
{
	public:
		Movement( void )
		{
			RequireComponent<Transform>();
		};
		void Update()
		{
			std::cout << "Update" << std::endl;
			std::vector< Entity >& entities = GetEntities();
			for (auto& entity : entities)
			{
				std::cout << "Update : " << entity.GetId() << std::endl;
							entity.GetComponent<Transform>().x += 1.0001f;
			}
		}
};

int main()
{
	Soon::ECS::Entity entite;
	Soon::ECS::Entity entite2;

	Transform& tr = entite.AddComponent<Transform>();
//	Transform& tre = entite2.AddComponent<Transform>();

	world.AddSystem<Movement>();
	entite.Activate();
	entite2.Activate();

	Soon::ECS::world.Update();

	Soon::ECS::world.GetSystem<Movement>().Update();

	std::cout << entite.GetComponent<Transform>().x << std::endl;

	return (0);
}
