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

			void Initialize( void );
			void Destroy( void );
			GLFWwindow* GetWindow( void );
			bool ShouldClose( void );
			void PollEvent( void );
			void DrawFrame( void );
			void Update( void );

		private:
			static OS*	_singleton;

			GLFWwindow*	_window;
	};
}
