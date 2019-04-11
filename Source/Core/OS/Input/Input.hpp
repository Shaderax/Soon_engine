namespace Soon
{
	class Input
	{
		public:
			Input( void );
			static Input* GetSingleton( void );
		private:
			static Input* _singleton;
	};
}
