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

	Soon::Object Maya;
	Maya.AddComponent<Soon::ObjFile>();
	Maya.GetComponent<Soon::ObjFile>().LoadObjFile("../Ressources/objects/Borderlands 2 - Maya/untitled.obj");

	float inc = 0;
	Maya.GetComponent<Transform3D>().Rotate(0.0f, 90.0f, 0.0f);
	while (!engine.ShouldEnd())
	{
//		inc = 0.1f;
//		Maya.GetComponent<Transform3D>().Rotate(0.0f, inc, 0.0f);
		lastTime = ShowFPS(lastTime);
		engine.Update();
		engine.DrawFrame();
	}
	return (0);
}
