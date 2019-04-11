#include <string>

namespace Soon
{
	class OS
	{
		public:

			static OS* GetSingleton( void );

			struct WindowAttribute
			{
				int		_width;
				int		_height;
				bool	_fullscreen;
				bool	_vsync;
				std::string _name;

				WindowAttribute( int width = 1280, int height = 720, bool fullscreen = false, bool vsync = false, std::string name = "New Project" ) :
					_width(width),
					_height(height),
					_fullscreen(fullscreen),
					_vsync(vsync),
					_name(name)
				{
				}
			};

			virtual OS::WindowAttribute GetWindowAttribute( void );
			virtual void* GetContext( void );

			OS( void );
		private:
			static OS*	_os;
	};
}
