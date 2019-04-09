namespace Soon
{
	void OSGLFW::Initialize( void )
	{
		InitGLFW();
		InitGLFWHints();
		_context = NewContextGL();
		_input = new GLFWInput;

//		_context.Initialize();
	}

	OSGLFW* NewOS( void )
	{
		OSGLFW* os = new OSGLFW;
//		InitWindowContext();
		return (os);
	}
}
