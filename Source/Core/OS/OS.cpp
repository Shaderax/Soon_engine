#include "Core/OS/OS.hpp"
#include "ContextHeaders.hpp"
#include "InitGLFW.hpp"
#include "GLFWInput.hpp"
#include "Graphics/GraphicsInstance.hpp"
#include "Graphics/GLFW/GLFWVulkan/GLFWVulkanRenderer.hpp"

namespace Soon
{
	OS *OS::_singleton = NULL;

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
		NewGraphicsInstance();
		GraphicsInstance::GetInstance()->Initialize();
		new GLFWVulkanRenderer();
		_window = GraphicsInstance::GetInstance()->GetContext();
		_input = new GLFWInput;
	}

	void OS::Destroy( void )
	{
		glfwTerminate();
	}

	GLFWwindow* OS::GetWindow( void )
	{
		return (_window);
	}

	OS::WindowAttribute OS::GetWindowAttribute( void )
	{
		return (_winAttr);
	}

	bool OS::ShouldClose( void )
	{
		return (glfwWindowShouldClose(_window));
	}

	void OS::PollEvent( void )
	{
		glfwPollEvents();
	}

	void OSGLFW::SwapBuffer( void )
	{
		glfwSwapBuffers(_window);
	}

	void OSGLFW::DrawFrame( void )
	{
		GraphicsInstance::GetInstance()->DrawFrame();
	}
	
	OS* NewOS( void )
	{
		OS* os = new OS;

		return (os);
	}
}
