#include "Core/Engine.hpp"
#include "Core/Math/vec3.hpp"
//#include "Components/TriangleRenderer.hpp"
//#include "Components/RecRenderer.hpp"
#include "Scene/Object.hpp"
#include "Core/Parsers/3DObject.hpp"
#include "Scene/3D/Components/Camera.hpp"

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

	Soon::Object Camera;
	std::cout << "ID Camera Object: " << Camera.GetId() << std::endl;
	Camera.AddComponent<Soon::Camera3D>();
	Soon::Object Triangle;
	Triangle.AddComponent<Soon::ObjFile>();
	Triangle.GetComponent<Soon::ObjFile>().LoadObjFile("../Ressources/objects/Borderlands 2 - Maya/untitled.obj");
	Camera.GetComponent<Transform3D>()._pos.z = 0.1f;
	while (!engine.ShouldEnd())
	{
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
