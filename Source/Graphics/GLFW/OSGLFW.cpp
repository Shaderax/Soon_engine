namespace Soon
{
	void OSGLFW::Initialize( void )
	{
		InitGLFW();
		InitGLFWHints();
		InitContextGL();
	}

	OSGLFW* NewOS( void )
	{
		OSGLFW* os = new OSGLFW;
//		InitWindowContext();
		return (os);
	}
}
