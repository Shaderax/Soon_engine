#pragma once

namespace Soon
{
	class Scene
	{
		public :
			Scene( void );
			~Scene( void );

			Camera* _currentCamera;
			std::vector<Object*>	_objects;
	}
}
