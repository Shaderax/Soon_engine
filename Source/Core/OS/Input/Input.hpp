namespace Soon
{
	class Input
	{
		public:
			static Input* GetSingleton( void );
		private:
			static Input* _singleton;
			Input( void );
	};
}
