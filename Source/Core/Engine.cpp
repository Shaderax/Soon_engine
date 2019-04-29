#include "Engine.hpp"
#include "ECS/World.hpp"
#include "Graphics/OSHeaders.hpp"

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

	bool Engine::Init( void )
	{
		NewOS();
		OS::GetSingleton()->Initialize();

		return (true);
	}

	void Engine::Destroy()
	{

	}

	void Engine::DrawFrame( void )
	{
		OS::GetSingleton()->DrawFrame();
		
	}

	void Engine::Update( void )
	{
		_world.Update();

//		OS::GetSingleton()->SwapBuffer();
		OS::GetSingleton()->PollEvent();
	}

	Engine& Engine::GetInstance( void )
	{
		static Engine engine;

		return (engine);
	}

	bool Engine::ShouldEnd( void )
	{
		return (OS::GetSingleton()->ShouldClose());
	}

	Scene& Engine::NewScene( void )
	{
		Scene* scene = new Scene();

		_currentScene = scene;
		_scenes.push_back(scene);
		return *(scene);
	}
}

