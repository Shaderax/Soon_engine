namespace
{
	bool InitGLFW( void )
	{
		if (!glfwInit())
		{
			printf("%s", "Failed to initialize GLFW\n");
			return (false);
		}
		return (true);
	}
}
