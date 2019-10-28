#include "Core/Engine.hpp"
#include "Utilities/ShowFps.hpp"
#include "Core/Scene/Object.hpp"
#include "Utilities/MeshArray.hpp"
#include "Core/Scene/3D/Components/Mesh.hpp"
#include "Core/Scene/3D/Components/Camera.hpp"
#include "Core/Scene/3D/Systems/3dObjectControlerSystem.hpp"
#include "Core/Scene/3D/Components/3dObjectControler.hpp"
#include "ECS/World.hpp"
#include "Core/Parsers/RessourceImporter.hpp"
#include "Core/Scene/Instantiate.hpp"

Soon::Engine& engine = Soon::Engine::GetInstance();

int main(int argc, char**argv)
{
	double lastTime = glfwGetTime();

	engine._world.AddSystem<ObjectControlerSystem>();

	Soon::Object Camera;
	Camera.AddComponent<Soon::Camera3D>();
	Camera.AddComponent<ObjectControler>();

//	Soon::Object Particles;
//	Particles.AddComponent<Soon::ParticlesSystem>();

	//Soon::MeshArray* ar = Soon::RessourceImporter::GetSingleton().Load<Soon::MeshArray>("../Ressources/Objects/Basics/Cube.obj");
	Soon::MeshArray* ar = Soon::RessourceImporter::GetSingleton().Load<Soon::MeshArray>("../Ressources/Objects/Borderlands 2 - Maya/untitled.obj");
	//Soon::MeshArray* ar = Soon::RessourceImporter::GetSingleton().Load<Soon::MeshArray>("../Ressources/Objects/Basics/Quad.obj");
	Soon::Object* Maya = Instantiate(*ar);

//	Soon::Object Sun;
//	Sun.AddComponent<Soon::DirectionalLight>();

	while (!engine.ShouldEnd())
	{
		lastTime = ShowFPS(lastTime);
		engine.Update();
		engine.DrawFrame();
	}

	Soon::Engine::ReleaseInstance();
	return (0);
}
