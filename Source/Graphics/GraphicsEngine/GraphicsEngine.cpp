#include "GraphicsEngine.hpp"

namespace Soon
{
	GraphicsEngine *GraphicsEngine::_singleton = nullptr;

	static GraphicsEngine* GraphicsEngine::GetSingleton()
	{
		return (_singleton);
	}

	GraphicsEngine::GraphicsEngine( void )
	{
		_singleton = this;
	}
}
