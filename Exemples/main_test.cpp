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

using namespace Soon;

Engine& engine = Engine::GetInstance();

int main(int argc, char**argv)
{
	double lastTime = glfwGetTime();

	engine._world.AddSystem<ObjectControlerSystem>();

	Object Camera;
	Camera.AddComponent<Camera3D>();
	Camera.AddComponent<ObjectControler>();

	MeshArray* ar = RessourceImporter::GetSingleton().Load<MeshArray>("../Ressources/Objects/Borderlands 2 - Maya/untitled.obj");
	Object* Maya = Instantiate(*ar);

	while (!engine.ShouldEnd())
	{
		lastTime = ShowFPS(lastTime);
		engine.Update();
		engine.DrawFrame();
	}

	RessourceImporter::GetSingleton().Unload<MeshArray>(ar->_path);
	Engine::ReleaseInstance();
	return (0);
}
