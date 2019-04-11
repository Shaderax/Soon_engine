#include "InitGLFW.hpp"
#include "OSGLFW.hpp"
#include "GLFWInput.hpp"
#include "ContextHeaders.hpp"

namespace Soon
{
	OSGLFW::OSGLFW( void )
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
}
