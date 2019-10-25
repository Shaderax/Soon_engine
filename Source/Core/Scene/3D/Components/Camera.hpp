#pragma once

#include "Core/Engine.hpp"
#include "Core/OS/OS.hpp"
#include "ECS/Component.hpp"
#include "ECS/Entity.hpp"
#include "Math/mat4.hpp"
#include "Math/vec3.hpp"
#include <math.h>
#include "Core/Renderer/Vulkan/GraphicsInstance.hpp"

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

				GraphicsInstance::WindowAttribute win = GraphicsInstance::GetInstance()->GetWindowAttribute();
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

				view.elem[3][0] = -pos.x;
				view.elem[3][1] = -pos.y;
				view.elem[3][2] = pos.z;

				return (view * _entity.GetComponent<Transform3D>()._rot.GetRotationMatrix());
			}

			mat4< float >	GetProjectionMatrix( void )
			{
				GraphicsInstance::WindowAttribute win = GraphicsInstance::GetInstance()->GetWindowAttribute();
				_aspect = (float)win._width / (float)win._height;

				mat4< float > proj;

				float scale = 1 / tan(_fov * M_PI / 180 / 2);

				proj(0, 0) = scale / _aspect;
				proj(1, 1) = -scale;
				proj(2, 2) = _far / (_near - _far);
				proj(2, 3) = -1;
				proj(3, 2) = (_near * _far) / (_near - _far);
				proj(3, 3) = 0;

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
