#include "Core/OS/OS.hpp"
#include "Graphics/GLFW/Init.hpp"
#include "Graphics/GLFW/Hints.hpp"
#include "Graphics/Vulkan/GraphicsInstance.hpp"
#include "Graphics/Vulkan/GraphicsRenderer.hpp"
#include <iostream>

namespace Soon
{
        OS* OS::_singleton = nullptr;

	OS::OS( void )
	{
		_singleton = this;
	}

	OS::~OS( void )
	{
		_singleton = nullptr;
		Destroy();
	}
	
	OS* OS::GetInstance( void )
        {
                return (_singleton);
        }

	void OS::Initialize( void )
	{
		InitGLFW();
		InitGLFWHints();
		new GraphicsInstance;
		new GraphicsRenderer;
		GraphicsInstance::GetInstance()->Initialize();
		GraphicsRenderer::GetInstance()->Initialize();
		_window = GraphicsInstance::GetInstance()->GetWindow();
	}

	void OS::Destroy( void )
	{
		glfwTerminate();
	}

	GLFWwindow* OS::GetWindow( void )
	{
		return (_window);
	}

	bool OS::ShouldClose( void )
	{
		return (glfwWindowShouldClose(_window));
	}

	void OS::PollEvent( void )
	{
		glfwPollEvents();
	}

	void OS::SwapBuffer( void )
	{
		glfwSwapBuffers(_window);
	}

	void OS::DrawFrame( void )
	{
		GraphicsInstance::GetInstance()->DrawFrame();
	}
	
	OS* NewOS( void )
	{
		OS* os = new OS;

		return (os);
	}

}
