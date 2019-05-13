#include "Core/OS/OS.hpp"
#include "Graphics/GLFW/InitGLFW.hpp"
#include "Core/OS/Input/Input.hpp"
#include "Graphics/Vulkan/GraphicsInstance.hpp"
#include "Graphics/Vulkan/GraphicsRenderer.hpp"

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
		new GraphicsInstance;
	//	NewGraphicsInstance();
		GraphicsInstance::GetInstance()->Initialize();
		_window = GraphicsInstance::GetInstance()->GetWindow();
		new GraphicsRenderer;
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
