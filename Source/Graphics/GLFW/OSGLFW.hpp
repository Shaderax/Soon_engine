#pragma once

#include "Core/OS/OS.hpp"
#include <GLFW/glfw3.h>
#include "Graphics/GLFW/GLFWInput.hpp"

namespace Soon
{
	class OSGLFW : OS
	{
		public:
			OSGLFW( void );
			virtual void Initialize( void );
			virtual void* GetContext( void );

		private:
			GLFWwindow*		_context;
			WindowAttribute	_winAttr;
			GLFWInput*		_input;
	};

	void InitOS( void );
}
