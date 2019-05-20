#pragma once

#include "Scene/Object.hpp"
#include <vector>

namespace Soon
{
	class Camera3D;

	class Scene
	{
		public:
			Scene( void );
			~Scene( void );
			void AddObject( Object* parent, Object& obj );

			 bool IsObjectInScene( Object& obj );
			 Camera3D* GetCurrentCamera( void );
			 void SetCurrentCamera( Camera3D* cam );
			
		private:
			std::vector< std::vector< Object > > Tree;
			Camera3D*		_camera;
	};
}
