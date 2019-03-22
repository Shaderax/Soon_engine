#include "Soon.hpp"
#include "Error.hpp"

namespace Soon
{
	bool	error(std::string msg)
	{
		std::cout << "Error : " << msg << std::endl;
		glfwTerminate();
		return (false);
	}
}

