#pragma once

#include "Core/Engine.hpp"
#include "ECS/Component.hpp"
#include "ECS/Entity.hpp"

namespace Soon
{
	class Camera3D : public Component
	{
		public:
			Camera3D( Entity& entity )
			{
				_entity = entity;
			}

			void MakeCurrent( void )
			{
				Engine::GetInstance().GetCurrentScene()->SetCurrentCamera(this);
			}
		private:
			Entity& _entite;
	};
}
