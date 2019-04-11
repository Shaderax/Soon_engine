namespace Soon
{
		ContextGL *ContextGL::singleton = NULL;

		ContextGL *ContextGL::GetSingleton( void )
		{
			return _singleton;
		}

		ContextGL::ContextGL( void )
		{
			singleton = this;
		}

		ContextGL::~ContextGL( void )
		{
			if (_singleton == this)
				_singleton = NULL;
		}
}
