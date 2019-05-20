#include "Core/Engine.hpp"
#include "Core/Math/vec3.hpp"
//#include "Components/TriangleRenderer.hpp"
//#include "Components/RecRenderer.hpp"
#include "Scene/Object.hpp"
#include "Core/Parsers/3DObject.hpp"
#include "Scene/3D/Components/Camera.hpp"

Soon::Engine& engine = Soon::Engine::GetInstance();

int main(int argc, char**argv)
{
	Soon::Object Triangle;
//	Triangle.AddComponent<Soon::TriangleRenderer>();
//	Triangle.AddComponent<Soon::RecRenderer>();
	Triangle.AddComponent<Soon::ObjFile>();
	Triangle.GetComponent<Soon::ObjFile>().LoadObjFile("../Ressources/objects/Borderlands 2 - Maya/untitled.obj");
	Soon::Object Camera;
	Camera.AddComponent<Soon::Camera3D>();
	while (!engine.ShouldEnd())
	{
		engine.Update();
		engine.DrawFrame();
	}
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
