namespace Soon
{
	class OS
	{
		public:

			static OS* GetSingleton( void );

		private:
			OS( void );
			static OS*	_os;

			struct WindowAttribute
			{
				int		_width;
				int		_height;
				bool	_fullscreen;
				bool	_vsync;

				WindowAttribute( int width = 1280, int height = 720, bool fullscreen = false, bool vsync = false ) :
					_width(width),
					_height(height),
					_fullscreen(fullscreen),
					_vsync(vsync)
				{
				}
			};
	};
}
