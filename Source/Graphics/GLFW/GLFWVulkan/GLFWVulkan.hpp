#pragma once

#include "Graphics/GraphicsInstance.hpp"
#include "GLFW/glfw3.h"
#include "vulkan/vulkan.h"

namespace Soon
{
	class GLFWVulkan : GraphicsInstance
	{
		public:
			GLFWVulkan( void );
			~GLFWVulkan( void );
			virtual void Initialize( void );
			virtual void Destroy( void );
			virtual void* GetContext( void );

			void CreateInstance( void );
			void CreateWindow( void );

		private:
			GLFWwindow*	_window;
			VkInstance	_vulkanInstance;
	};

	void NewGraphicsInstance( void );
}
