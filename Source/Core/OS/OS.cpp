#include "Core/OS/OS.hpp"
#include "Core/Renderer/GLFW/Init.hpp"
#include "Core/Renderer/GLFW/Hints.hpp"
#include "Core/Renderer/Vulkan/GraphicsInstance.hpp"
#include "Core/Renderer/Vulkan/GraphicsRenderer.hpp"
#include <iostream>

namespace Soon
{
        OS* OS::_singleton = nullptr;

	OS::OS( void )
	{
		//_singleton = this;
	}

	OS::~OS( void )
	{
		//_singleton = nullptr;
		Destroy();
	}
	
	OS* OS::GetInstance( void )
        {
		if (!_singleton)
			_singleton = new OS;

                return (_singleton);
        }

	void OS::Initialize( void )
	{
		InitGLFW();
		InitGLFWHints();
		GraphicsInstance::GetInstance()->Initialize();
		GraphicsRenderer::GetInstance()->Initialize();
		_window = GraphicsInstance::GetInstance()->GetWindow();
	}

	void OS::Update( void )
	{
		if (GraphicsRenderer::GetInstance()->IsChange())
		{
			GraphicsInstance::GetInstance()->FillCommandBuffer();
			GraphicsRenderer::GetInstance()->ResetChange();
		}
	}

	void OS::Destroy( void )
	{
		GraphicsInstance::GetInstance()->Destroy();
		GraphicsRenderer::GetInstance()->Destroy();
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

//	void OS::SwapBuffer( void )
//	{
//		if (_window)
//			glfwSwapBuffers(_window);
//	}

	void OS::DrawFrame( void )
	{
		GraphicsInstance::GetInstance()->DrawFrame();
	}
}
