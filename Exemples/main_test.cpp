#include "Core/Engine.hpp"
#include "Core/Math/vec3.hpp"

Soon::Engine& engine = Soon::Engine::GetInstance();

int main(int argc, char**argv)
{
	while (!engine.ShouldEnd())
	{
		engine.Update();
		engine.DrawFrame();
	}
	//	Scene& scene = engine.NewScene();
	//
	//	Object& object1 = scene.NewObjectInScene();
	//
	//	object1.AddComponent<GravityComponent>();
	//
	//	engine._world.AddSystem<GravitySystem>();
	//
	//	engine.Update();

	return (0);
}
