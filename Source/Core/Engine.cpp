#include "Error.hpp"
#include <stdio.h>

namespace Soon
{
	Engine::Engine( void ) :
		_world(Soon::ECS::World::GetInstance())
	{
		
	}

	bool	Engine::InitGlfw( void )
	{
		if (!glfwInit())
		{
			printf("%s", "Failed to initialize GLFW\n");
			return (false);
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR_VERSION);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR_VERSION);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
# if __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
# endif
		return (true);
	}

	bool Engine::Init( void )
	{
		if (!InitGlfw())
			return (Soon::error("glfw init"));
		return (true);
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

