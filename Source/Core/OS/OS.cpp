#include "Core/OS/OS.hpp"

namespace Soon
{
	OS *OS::_singleton = NULL;

	OS::OS( void )
	{
		_singleton = this;
	}

	OS::~OS( void )
	{
		_singleton = nullptr;
	}

	OS* OS::GetSingleton( void )
	{
		return (_singleton);
	}
}
