#pragma once

#include "Core/Scene/Scene.hpp"
#include <vector>

namespace Soon
{
	class Engine
	{
		public:
			static Engine& GetInstance( void );
			bool Init( void );
			void Update( void );
			Scene& NewScene( void );
			void Destroy( void );
			bool ShouldEnd( void );

			Scene* GetCurrentScene( void );

			void DrawFrame( void );

			~Engine( void );

			Soon::ECS::World&		_world;
		private:
			Engine( void );

			Scene*					_currentScene;
			std::vector< Scene* >	_scenes;

	};
}
