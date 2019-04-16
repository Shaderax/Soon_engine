#include "Graphics/GraphicsInstance.hpp"

namespace Soon
{
	GraphicsInstance *GraphicsInstance::_instance = nullptr;

	GraphicsInstance::GraphicsInstance( void )
	{
		_instance = this;
	}

	GraphicsInstance* GraphicsInstance::GetInstance()
	{
		return (_instance);
	}
}
