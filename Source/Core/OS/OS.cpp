#include "Core/OS/OS.hpp"

namespace Soon
{
	OS *OS::_singleton = NULL;

	OS::OS( void )
	{
		_singleton = this;
	}
}
