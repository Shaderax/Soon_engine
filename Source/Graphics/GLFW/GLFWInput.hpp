namespace Soon
{
	class GLFWInput : Input
	{
		public:
			bool GetKeyDown( int key );

		private:
			float _lastX;
			float _lastY;
	};
}
