#include "Core/Engine.hpp"
#include "Core/Math/vec3.hpp"
//#include "Components/TriangleRenderer.hpp"
//#include "Components/RecRenderer.hpp"
#include "Scene/Object.hpp"
#include "Core/Parsers/3DObject.hpp"
#include "Scene/3D/Components/Camera.hpp"
#include "Scene/3D/Components/3dObjectControler.hpp"
#include "Scene/3D/Systems/3dObjectControlerSystem.hpp"
#include "ECS/World.hpp"

Soon::Engine& engine = Soon::Engine::GetInstance();

double ShowFPS( double lastTime )
{
	static int nbFrames = 0;
	double currentTime = glfwGetTime();

	if ( currentTime - lastTime >= 1.0 )
	{
  //       	printf("%f ms/frame\n", 1000.0/double(nbFrames));
		printf("%d fps\n", nbFrames);
		nbFrames = 0;
		lastTime += 1.0;
	}
	nbFrames++;

     return lastTime;
}
int main(int argc, char**argv)
{
	double lastTime = glfwGetTime();

	engine._world.AddSystem<ObjectControlerSystem>();
	Soon::Object Camera;
	Camera.AddComponent<Soon::Camera3D>();
	Camera.AddComponent<ObjectControler>();

	Soon::Object Triangle;
	Triangle.AddComponent<Soon::ObjFile>();
	Triangle.GetComponent<Soon::ObjFile>().LoadObjFile("../Ressources/objects/Borderlands 2 - Maya/untitled.obj");

	while (!engine.ShouldEnd())
	{
//		Camera.GetComponent<Transform3D>()._pos.z -= 0.001f;
		lastTime = ShowFPS(lastTime);
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
