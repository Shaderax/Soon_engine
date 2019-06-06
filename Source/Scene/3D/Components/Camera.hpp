#pragma once

#include "Core/Engine.hpp"
#include "Core/OS/OS.hpp"
#include "ECS/Component.hpp"
#include "ECS/Entity.hpp"
#include "Core/Math/mat4.hpp"
#include "Core/Math/vec3.hpp"
#include <math.h>

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

				_fov = 45.0f;
				_near = 0.05f;
				_far = 100.0f;

				OS::WindowAttribute win = OS::GetInstance()->GetWindowAttribute();
				_aspect = win._width / win._height;

				MakeCurrent();
			}

			void MakeCurrent( void )
			{
				Engine::GetInstance().GetCurrentScene()->SetCurrentCamera(this);
			}

			mat4<float> GetViewMatrix( void )
			{
				mat4<float> view;

				vec3<float> pos = _entity.GetComponent<Transform3D>()._pos;
//				mat4<float> mm = _entity.GetComponent<Transform3D>()._rot.GetRotationMatrix();
//				_target = pos + vec3<float>(0.0f, 0.0f, 1.0f);
//
//				vec3<float> cameraDirection = (pos - _target).Normalize();
//
//				vec3<float> cameraRight = _up.Cross(cameraDirection).Normalize();
//
//				vec3<float> cameraUp = cameraDirection.Cross(cameraRight);

//				view.elem[0][0] = cameraRight.x;
//				view.elem[0][1] = cameraRight.y;
//				view.elem[0][2] = cameraRight.z;
//
//				view.elem[1][0] = cameraUp.x;
//				view.elem[1][1] = cameraUp.y;
//				view.elem[1][2] = cameraUp.z;
//
//				view.elem[2][0] = cameraDirection.x;
//				view.elem[2][1] = cameraDirection.y;
//				view.elem[2][2] = cameraDirection.z;

				view.elem[3][0] = -pos.x;
				view.elem[3][1] = -pos.y;
				view.elem[3][2] = pos.z;

				return (view * _entity.GetComponent<Transform3D>()._rot.GetRotationMatrix());
			}

			mat4< float >	GetProjectionMatrix( void )
			{
				OS::WindowAttribute win = OS::GetInstance()->GetWindowAttribute();
				_aspect = (float)win._width / (float)win._height;

				mat4< float > proj;

				float scale = 1 / tan(_fov * M_PI / 180 / 2);

				proj(0, 0) = scale / _aspect;
				proj(1, 1) = -scale;
				proj(2, 2) = _far / (_near - _far);
				proj(2, 3) = -1;
				proj(3, 2) = (_near * _far) / (_near - _far);
				proj(3, 3) = 0;

//				float scale = 1 / tan(_fov / 2);

//				proj(0, 0) = scale;
//				proj(1, 1) = (scale / _aspect);
//				proj(2, 2) = -((_far + _near) / (_far - _near));
//				proj(2, 3) = -((2 * _far * _near) / (_far - _near));
//				proj(3, 2) = -1;
//				proj(3, 3) = 0;


//				float scale;
//				float l;
//				float r;
//				float b;
//				float t;
//
//				scale = tan(_fov * 0.5 * (M_PI / 180)) * _near;
//				t = scale;
//				b = -scale;
//				r = scale * _aspect;
//				l = -r;
//				proj(0,0) = (2 * _near) / (r - l);
//				proj(0,2) = (r + l) / (r - l);
//				proj(1,1) = -((2 * _near) / (t - b));
//				proj(1,2) = (t + b) / (t - b);
//				proj(2,2) = -((_far + _near) / (_far - _near));
//				proj(2,3) = -((2 * _far * _near) / (_far - _near));
//				proj(3,2) = -1;
				return (proj);
			}

			void SetTarget(vec3<float> target)
			{
				_target = target;
			}

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
