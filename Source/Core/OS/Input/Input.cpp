#include "Input.hpp"

namespace Soon
{
	Input *Input::_singleton = NULL;

	Input* Input::GetSingleton( void )
	{
		return (_singleton);
	}
	
	Input::Input( void )
	{
		_singleton = this;
	}
}
