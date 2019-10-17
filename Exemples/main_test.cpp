#include "Core/Engine.hpp"
#include "Core/Math/vec3.hpp"
#include "Scene/Object.hpp"
#include "Scene/3D/Components/Mesh.hpp"
#include "Scene/3D/Components/Camera.hpp"
#include "Scene/3D/Components/3dObjectControler.hpp"
#include "Scene/3D/Systems/3dObjectControlerSystem.hpp"
#include "ECS/World.hpp"
//#include "Scene/3D/Components/DirectionalLight.hpp"
#include "Scene/3D/Components/ParticlesSystem.hpp"
#include "Utilities/MeshArray.hpp"
#include "Core/Parsers/RessourceImporter.hpp"
#include "Scene/Instantiate.hpp"

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

//	Soon::Object Particles;
//	Particles.AddComponent<Soon::ParticlesSystem>();
//	Soon::Object Maya;
//	Soon::Mesh& mesh = Maya.AddComponent<Soon::Mesh>((*ar)[2]);
//	mesh.EnableRender();
//	Soon::Object* Maya = Instantiate(*ar);
	
	Soon::MeshArray* ar = Soon::RessourceImporter::GetSingleton().Load<Soon::MeshArray>("../Ressources/objects/Borderlands 2 - Maya/untitled.obj");
	Soon::Object* Maya = Instantiate(*ar);
	ar = Soon::RessourceImporter::GetSingleton().Load<Soon::MeshArray>("../Ressources/objects/Basics/Cube.obj");
	Instantiate(*ar);

//	Maya.GetComponent<Soon::Mesh>().LoadMesh("../Ressources/objects/Borderlands 2 - Maya/untitled.obj");
//	Maya.GetComponent<Soon::Mesh>().LoadMesh("../Ressources/objects/Borderlands 2 - Maya/maya.obj");
//	Maya.GetComponent<Soon::Mesh>().LoadMesh("../Ressources/objects/Test/test.obj");
//	Maya.GetComponent<Soon::Mesh>().LoadMesh("../Ressources/objects/Test/cat.obj");
//	Maya.GetComponent<Soon::Mesh>().LoadMesh("../Ressources/objects/Test/nanosuit.obj");
//	Maya.GetComponent<Soon::Mesh>().LoadMesh("../Ressources/objects/Test/chalet.obj");
//	Maya.GetComponent<Soon::Mesh>().LoadMesh("../Ressources/objects/Test/IronMan.obj");

//	Soon::Object Sun;
//	Sun.AddComponent<Soon::DirectionalLight>();

	while (!engine.ShouldEnd())
	{
		lastTime = ShowFPS(lastTime);
		engine.Update();
		engine.DrawFrame();
	}
	return (0);
}
