namespace Soon
{
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
}
