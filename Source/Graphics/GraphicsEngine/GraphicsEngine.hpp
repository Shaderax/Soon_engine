namespace Soon
{
	class GraphicsEngine
	{
		public:
			static GraphicsEngine* GetSingleton();

		private:
			GraphicsEngine( void );
			static GraphicsEngine* _singleton;
	}
}
