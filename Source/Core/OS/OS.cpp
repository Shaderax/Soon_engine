namespace Soon
{
	class OS
	{
		public:

		static OS* GetSingleton( void );

		private:
			OS( void );
			static OS*	_os;
	};
}
