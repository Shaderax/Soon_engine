#pragma once

#include "Graphics/GLFW/GLFWVulkan/GLFWVulkan.hpp"

namespace Soon
{
	class GraphicsInstance
	{
		public:
			GraphicsInstance( void );

			virtual void Initialize( void ) = 0;
			virtual void CreateInstance( void ) = 0;
			virtual void* GetContext( void ) = 0;
			virtual void DrawFrame( void ) = 0;
			virtual void RecreateCommandBuffer( void ) = 0;
			BufferRenderer CreateVertexBuffer( VertexBufferInfo inf );

			static GraphicsInstance* GetInstance( void );

		private:

			static GraphicsInstance* _instance;
	};
}
