#include "Graphics/GraphicsRenderer.hpp"

namespace Soon
{
	GraphicsRenderer *GraphicsRenderer::_instance = nullptr;

	GraphicsRenderer::GraphicsRenderer( void )
	{
		_instance = this;
	}

	GraphicsRenderer* GraphicsRenderer::GetInstance()
	{
		return (_instance);
	}
}
