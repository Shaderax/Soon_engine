#pragma once
#include <string>
#include "Graphics/Vulkan/GraphicsInstance.hpp"
//#define GLFW_INCLUDE_VULKAN
//#include <GLFW/glfw3.h>
#include "Core/OS/Input/Input.hpp"

namespace Soon
{
	class OS
	{
		public:
			OS( void );
			~OS( void );

			static OS* GetInstance( void );

			struct WindowAttribute
			{
				uint32_t	_width;
				uint32_t	_height;
				bool		_fullscreen;
				bool		_vsync;
				std::string _name;

				WindowAttribute( int width = 1280, int height = 720, bool fullscreen = false, bool vsync = false, std::string name = "New Project" ) :
					_width(width),
					_height(height),
					_fullscreen(fullscreen),
					_vsync(vsync),
					_name(name)
				{
				}
			};

			void Initialize( void );
			void Destroy( void );
			GLFWwindow* GetWindow( void );
			OS::WindowAttribute GetWindowAttribute( void );
			void SetGetWindowSizeAttribute( int width, int height);
			bool ShouldClose( void );
			void PollEvent( void );
			void SwapBuffer( void );
			void DrawFrame( void );
		private:
			static OS*	_singleton;

			GLFWwindow*     _window;
			WindowAttribute _winAttr;
			Input*      _input;
	};
	OS* NewOS( void );
}
