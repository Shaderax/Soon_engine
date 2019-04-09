namespace Soon
{
	class OSGLFW : OS
	{
		public:
		virtual void Initialize( void );
		private:
		GLFWwindow* _context;
		WindowAttribute _winAttr;
		GLFWInput*	_input;
	};

	void InitOS( void );
}
