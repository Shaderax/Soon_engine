#pragma once

namespace Soon
{
	class Input
	{
		public:
			Input( void );
			static Input* GetSingleton( void );
			bool GetKeyDown( int key );
		private:
			static Input* _singleton;

			float _lastX;
			float _lastY;
	};
}
