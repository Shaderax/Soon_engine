#pragma once

#include <iostream>
#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

namespace Soon
{
	class GraphicsRenderer
	{
		public:
			GraphicsRenderer( void );
			~GraphicsRenderer( void );

			static GraphicsRenderer* GetInstance( void );

			virtual std::vector< VkBuffer > GetvkBuffers( void ) = 0;
			virtual std::vector< size_t > GetNbVertex( void ) = 0;
			virtual bool HasChange( void ) = 0;
			virtual void SetChangeFalse( void ) = 0;
		private:

			static GraphicsRenderer* _instance;
	};
}
