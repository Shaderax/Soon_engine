#include "Engine.hpp"
#include "Core/OS/OS.hpp"
#include "ECS/World.hpp"
#include "Core/Renderer/Vulkan/GraphicsRenderer.hpp"
#include "Core/Renderer/Vulkan/GraphicsInstance.hpp"

#include "Core/Parsers/InitRessourceImporter.hpp"

namespace Soon
{
	Engine::Engine( void ) :
		_world(Soon::ECS::World::GetInstance())
	{
		Init();
	}
	
	Engine::~Engine( void )
	{
		Destroy();
	}

	Engine& Engine::GetInstance( void )
	{
		static Engine engine;

		return (engine);
	}

	bool Engine::Init( void )
	{
		InitRessourceImporter();
		OS::GetInstance()->Initialize();
		NewScene();

		return (true);
	}

	void Engine::Destroy()
	{
		OS::GetInstance()->Destroy();
	}

	void Engine::Update( void )
	{
		_world.Update();

		OS::GetInstance()->Update();
	}

	void Engine::DrawFrame( void )
	{
		OS::GetInstance()->PollEvent();
		OS::GetInstance()->DrawFrame();
	}

	bool Engine::ShouldEnd( void )
	{
		return (OS::GetInstance()->ShouldClose());
	}

	Scene& Engine::NewScene( void )
	{
		Scene* scene = new Scene();

		_currentScene = scene;
		_scenes.push_back(scene);
		return *(scene);
	}

	Scene* Engine::GetCurrentScene( void )
	{
		return (_currentScene);
	}
}
