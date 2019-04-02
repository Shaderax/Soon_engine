namespace
{
	void InitGLFWOpenGLHints( void )
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, @OPENGL_MAJOR_VERSION@);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, @OPENGL_MINOR_VERSION@);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		return (true);

	}
}
