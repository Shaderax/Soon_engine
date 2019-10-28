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
			static void ReleaseInstance( void );
			static OS* _instance;

			void Initialize( void );
			GLFWwindow* GetWindow( void );
			bool ShouldClose( void );
			void PollEvent( void );
			void DrawFrame( void );
			void Update( void );

		private:
			GLFWwindow*	_window;
	};
}
