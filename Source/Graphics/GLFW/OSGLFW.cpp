namespace Soon
{
	void OSGLFW::Initialize( void )
	{
		InitGLFW();
		InitGLFWHints();
		_context = NewContextGL();
		_context.Initialize();
	}

	OSGLFW* NewOS( void )
	{
		OSGLFW* os = new OSGLFW;
//		InitWindowContext();
		return (os);
	}
}
