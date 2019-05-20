#pragma once

#include "Scene/Scene.hpp"
#include <vector>

namespace Soon
{
	class Engine
	{
		public:
			void Update( void );
			bool Init( void );
			static Engine& GetInstance( void );
			Scene& NewScene( void );
			void Destroy( void );
			bool ShouldEnd( void );

			Scene* GetCurrentScene( void );

			void DrawFrame( void );

			~Engine( void );

		private:
			Engine( void );

			Scene*					_currentScene;
			std::vector< Scene* >	_scenes;

			Soon::ECS::World&		_world;
	};
}
