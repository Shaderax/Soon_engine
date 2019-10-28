#include "Engine.hpp"
#include "Core/OS/OS.hpp"
#include "ECS/World.hpp"
#include "Core/Renderer/Vulkan/GraphicsRenderer.hpp"
#include "Core/Renderer/Vulkan/GraphicsInstance.hpp"

#include "Core/Parsers/InitRessourceImporter.hpp"

namespace Soon
{
	Engine* Engine::_instance = nullptr;

	Engine::Engine( void ) :
		_world(Soon::ECS::World::GetInstance())
	{
		Init();
	}
	
	Engine::~Engine( void )
	{
		OS::ReleaseInstance();
		_currentScene = nullptr;
		for (Scene* scene : _scenes)
			delete scene;
	}

	Engine& Engine::GetInstance( void )
	{
		if (!_instance)
			_instance = new Engine;

		return (*_instance);
	}

	void Engine::ReleaseInstance( void )
	{
		if (_instance)
		{
			delete _instance;
			_instance = nullptr;
		}
	}

	bool Engine::Init( void )
	{
		InitRessourceImporter();
		OS::GetInstance()->Initialize();
		NewScene();

		return (true);
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
