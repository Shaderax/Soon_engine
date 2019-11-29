#include "Core/OS/OS.hpp"
#include "Core/Renderer/Vulkan/GraphicsInstance.hpp"
#include "Core/Renderer/Vulkan/GraphicsRenderer.hpp"
#include <iostream>

namespace Soon
{
	OS* OS::_instance = nullptr;

	OS::OS( void )
	{

	}

	OS::~OS( void )
	{
		GraphicsRenderer::ReleaseInstance();
		GraphicsInstance::ReleaseInstance();
	}
	
	OS* OS::GetInstance( void )
        {
		if (!_instance)
			_instance = new OS;

                return (_instance);
        }

	void OS::ReleaseInstance( void )
        {
		if (_instance)
		{
			delete _instance;
			_instance = nullptr;

		}
        }

	void OS::Initialize( void )
	{
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

	GLFWwindow* OS::GetWindow( void )
	{
		return (_window);
	}

	bool OS::ShouldClose( void )
	{
		return (GraphicsInstance::GetInstance()->ShouldClose(_window));
	}

	void OS::PollEvent( void )
	{
		GraphicsInstance::GetInstance()->PollEvent();
	}

	void OS::DrawFrame( void )
	{
		GraphicsInstance::GetInstance()->DrawFrame();
	}
}
