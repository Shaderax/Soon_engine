#include "Core/Engine.hpp"
#include "Core/Math/vec3.hpp"

struct Vertex
{
	vec3<float> pos;
	vec3<float> color;
};

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
