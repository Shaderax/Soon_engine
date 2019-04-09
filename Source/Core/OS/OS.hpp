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
				std::string _name;

				WindowAttribute( int width = 1280, int height = 720, bool fullscreen = false, bool vsync = falsem std::string name = "New Project" ) :
					_width(width),
					_height(height),
					_fullscreen(fullscreen),
					_vsync(vsync),
					_name(name)
				{
				}
			};
	};
}
