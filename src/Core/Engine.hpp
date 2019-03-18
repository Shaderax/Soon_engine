#pragma once

#include <vector>

namepsace Soon
{
	class Engine
	{
		public:
			void Update( void );
	bool Init( void )
			static Engine* GetInstance( void );
		private:
	bool	InitGlfw( void )
			std::vector<Scene> Scenes;
	};
}

