namespace Soon
{
	void GLFWOpenGLContext::Initialize( void )
	{
		_context = glfwCreateWindow(width, height, name_window, NULL, NULL);
	}


	GLFWOpenGLContext* NewContextGL( void )
	{
		GLFWOpenGLContext* context = new GLFWOpenGLContext;
		return (context);
	}
}
