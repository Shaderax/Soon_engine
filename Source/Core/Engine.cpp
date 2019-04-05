#include "Error.hpp"
#include <stdio.h>

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
		_os = NewOS();
		_os->Initialize();

		return (true);
	}

	void Engine::InitGraphics( void )
	{
//		InitGraphicsGLFWOpenGL();
	}

	void Engine::Destroy()
	{
		delete _os;
	}

	void Engine::Update( void )
	{
		_world.Update();
	}

	static Engine& Engine::GetInstance( void )
	{
		static Engine engine;

		return (engine);
	}

	Scene& Engine::NewScene( void )
	{
		Scene* scene = new Scene();

		_currentScene = scene;
		_scenes.push_back(scene);
		return *(scene);
	}
}

