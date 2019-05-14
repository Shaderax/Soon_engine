#include "Core/Engine.hpp"
#include "Core/Math/vec3.hpp"
#include "Components/TriangleRenderer.hpp"
#include "Scene/Object.hpp"

Soon::Engine& engine = Soon::Engine::GetInstance();

int main(int argc, char**argv)
{
	Soon::Object Triangle;
	Triangle.AddComponent<Soon::TriangleRenderer>();
//	while (!engine.ShouldEnd())
//	{
		engine.Update();
		engine.DrawFrame();
//	}
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
