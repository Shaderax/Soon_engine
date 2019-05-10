#include "ContextHeaders.hpp"
#include "InitGLFW.hpp"
#include "OSGLFW.hpp"
#include "GLFWInput.hpp"
#include "Graphics/GraphicsInstance.hpp"
#include "Graphics/GLFW/GLFWVulkan/GLFWVulkanRenderer.hpp"

namespace Soon
{
	OSGLFW::OSGLFW( void )
	{

	}

	OSGLFW::~OSGLFW( void )
	{
		Destroy();
	}

	void OSGLFW::Initialize( void )
	{
		InitGLFW();
		InitGLFWHints();
		NewGraphicsInstance();
		GraphicsInstance::GetInstance()->Initialize();
		new GLFWVulkanRenderer();
		_window = static_cast<GLFWwindow*>(GraphicsInstance::GetInstance()->GetContext());
		_input = new GLFWInput;
	}

	void OSGLFW::Destroy( void )
	{
		glfwTerminate();
	}

	OSGLFW* NewOS( void )
	{
		OSGLFW* os = new OSGLFW;

		return (os);
	}

	void* OSGLFW::GetContext( void )
	{
		return (_window);
	}

	OS::WindowAttribute OSGLFW::GetWindowAttribute( void )
	{
		return (_winAttr);
	}

	bool OSGLFW::ShouldClose( void )
	{
		return (glfwWindowShouldClose(_window));
	}

	void OSGLFW::PollEvent( void )
	{
		glfwPollEvents();
	}

//	void OSGLFW::ClearColor(float r, float g, float b)
//	{
//		glClearColor(r, g, b, 1.0f);
//	}

	void OSGLFW::SwapBuffer( void )
	{
		glfwSwapBuffers(_window);
	}

	void OSGLFW::DrawFrame( void )
	{
		GraphicsInstance::GetInstance()->DrawFrame();
	}
}
