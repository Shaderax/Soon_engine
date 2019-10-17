#pragma once
#include <string>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

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
			bool ShouldClose( void );
			void PollEvent( void );
			void SwapBuffer( void );
			void DrawFrame( void );

			OS::WindowAttribute GetWindowAttribute( void )
			{
				return (_winAttr);
			}

			void SetWindowSizeAttribute( int width, int height)
			{
				_winAttr._width = width;
				_winAttr._height = height;
			}
		private:
			static OS*	_singleton;

			GLFWwindow*     _window;
			WindowAttribute _winAttr;
			//		Input*      _input;
	};
	OS* NewOS( void );
}
