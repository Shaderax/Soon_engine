namespace Soon
{
	bool GLFWInput::GetKeyDown( int key )
	{
		return (glfwGetKey(OS::GetSingleton()->GetContext(), key) == GLFW_PRESS)
	}
}
