#pragma once

#include "ContextHeaders.hpp"
#include "Core/OS/OS.hpp"
#include <GLFW/glfw3.h>
#include "Graphics/GLFW/GLFWInput.hpp"

namespace Soon
{
	class OSGLFW : OS
	{
		public:
			OSGLFW( void );
			~OSGLFW( void );
			virtual void Initialize( void );
			virtual void Destroy( void );
			virtual void* GetContext( void );
			virtual OS::WindowAttribute GetWindowAttribute( void );
			virtual bool ShouldClose( void );
			virtual void PollEvent( void );
			virtual void SwapBuffer( void );

		private:
			GLFWwindow*		_window;
			WindowAttribute	_winAttr;
			GLFWInput*		_input;
	};

	OSGLFW* NewOS( void );
}
