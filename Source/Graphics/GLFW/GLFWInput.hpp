#pragma once

#include "Core/OS/Input/Input.hpp"

namespace Soon
{
	class GLFWInput : Input
	{
		public:
			GLFWInput( void );
			bool GetKeyDown( int key );

		private:
			float _lastX;
			float _lastY;
	};
}
