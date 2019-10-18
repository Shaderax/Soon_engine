#include "Core/Engine.hpp"
#include "Core/Math/vec3.hpp"
#include "Scene/Object.hpp"
#include "Scene/3D/Components/Mesh.hpp"
#include "Scene/3D/Components/Camera.hpp"
#include "Scene/3D/Components/3dObjectControler.hpp"
#include "Scene/3D/Systems/3dObjectControlerSystem.hpp"
#include "ECS/World.hpp"
#include "Scene/3D/Components/ParticlesSystem.hpp"
#include "Utilities/MeshArray.hpp"
#include "Core/Parsers/RessourceImporter.hpp"
#include "Scene/Instantiate.hpp"
#include "Utilities/ShowFps.hpp"

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

	Soon::MeshArray* ar = Soon::RessourceImporter::GetSingleton().Load<Soon::MeshArray>("../Ressources/objects/Borderlands 2 - Maya/untitled.obj");
	Soon::Object* Maya = Instantiate(*ar);

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
