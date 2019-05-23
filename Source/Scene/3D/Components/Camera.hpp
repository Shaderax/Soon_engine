#pragma once

#include "Core/Engine.hpp"
#include "ECS/Component.hpp"
#include "ECS/Entity.hpp"
#include "Core/Math/mat4.hpp"
#include "Core/Math/vec3.hpp"

namespace Soon
{
	class Camera3D : public Component
	{
		public:
			Camera3D( Entity& entity )
			{
				_entity = entity;
				_target = vec3<float>(0.0f, 0.0f, 0.0f);
				_up = vec3<float>(0.0f, 1.0f, 0.0f);
			}

			void MakeCurrent( void )
			{
				Engine::GetInstance().GetCurrentScene()->SetCurrentCamera(this);
			}

			mat4<float> GetViewMatrix( void )
			{
				mat4<float> view;

				vec3<float> pos = _entity.GetComponent<Transform3D>()._pos;

				vec3<float> cameraDirection = (pos - _target).Normalize();

				vec3<float> cameraRight = _up.Cross(cameraDirection).Normalize();

				vec3<float> cameraUp = cameraDirection.Cross(cameraRight);

				view.elem[0][0] = cameraRight.x;
				view.elem[0][1] = cameraRight.y;
				view.elem[0][2] = cameraRight.z;

				view.elem[1][0] = cameraUp.x;
				view.elem[1][1] = cameraUp.y;
				view.elem[1][2] = cameraUp.z;

				view.elem[2][0] = cameraDirection.x;
				view.elem[2][1] = cameraDirection.y;
				view.elem[2][2] = cameraDirection.z;

				view.elem[0][3] = -pos.x;
				view.elem[1][3] = -pos.y;
				view.elem[2][3] = -pos.z;

				return (view);
			}

			void SetTarget(vec3<float> target)
			{
				_target = target;
			}

		private:
			Entity		_entity;
			vec3<float>	_target;
			vec3<float>	_up;
	};
}
