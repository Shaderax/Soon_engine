#pragma once

#include "ECS/Component.hpp"
#include "ECS/Entity.hpp"
#include "Math/mat4.hpp"
#include "Math/vec3.hpp"

namespace Soon
{
	class Camera3D : public Component
	{
		public:
			Camera3D( Entity& entity );

			void MakeCurrent( void );

			mat4<float> GetViewMatrix( void );

			mat4< float >	GetProjectionMatrix( void );

			void SetTarget(vec3<float> target);

		private:
			Entity		_entity;
			vec3<float>	_target;
			vec3<float>	_up;

			float _fov;
			float _near;
			float _far;
			float _aspect;
	};
}
