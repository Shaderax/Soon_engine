#include "InitGLFW.hpp"
#include "OSGLFW.hpp"
#include "GLFWInput.hpp"
#include "ContextHeaders.hpp"

namespace Soon
{
	OSGLFW::OSGLFW( void ) : _context(nullptr)
	{

	}

	OSGLFW::~OSGLFW( void )
	{

	}

	void OSGLFW::Initialize( void )
	{
		InitGLFW();
		InitGLFWHints();
		_context = NewContextGL();
		_input = new GLFWInput;
	}

	OSGLFW* NewOS( void )
	{
		OSGLFW* os = new OSGLFW;

		return (os);
	}

	void* OSGLFW::GetContext( void )
	{
		return (_context);
	}

	OS::WindowAttribute OSGLFW::GetWindowAttribute( void )
	{
		return (_winAttr);
	}

	bool OSGLFW::ShouldClose( void )
	{
		return (glfwWindowShouldClose(_context));
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
		glfwSwapBuffers(_context);
	}
}
