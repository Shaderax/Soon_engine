#pragma once

namespace Soon
{
	class ContextGL
	{
		public:
			ContextGL *GetSingleton( void );

			ContextGL( void );

			~ContextGL( void );

		private:
			static ContextGL *singleton;

	};
}
