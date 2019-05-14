#include "Engine.hpp"
#include "Core/OS/OS.hpp"
#include "ECS/World.hpp"
#include "Graphics/Vulkan/GraphicsRenderer.hpp"

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
		new OS;
//		NewOS();
		OS::GetInstance()->Initialize();

		return (true);
	}

	void Engine::Destroy()
	{

	}

	void Engine::DrawFrame( void )
	{
		OS::GetInstance()->DrawFrame();
	}

	void Engine::Update( void )
	{
		_world.Update();

		if (GraphicsRenderer::GetInstance()->HasChange())
		{
			GraphicsInstance::GetInstance()->RecreateCommandBuffer();
			GraphicsRenderer::GetInstance()->SetChangeFalse();
		}
		OS::GetInstance()->PollEvent();
	}

	Engine& Engine::GetInstance( void )
	{
		static Engine engine;

		return (engine);
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
}

