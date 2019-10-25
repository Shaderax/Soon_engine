#pragma once

#include "ECS/System.hpp"
#include "Core/Math/vec3.hpp"
#include "Core/OS/Input/Input.hpp"

struct ObjectControlerSystem : public System
{
	public :
		ObjectControlerSystem( void )
		{
			RequireComponent<ObjectControler>();
		}

		~ObjectControlerSystem( void )
		{

		}

		void Update( void )
		{
			std::vector< Entity > entities = GetEntities();
			vec3<float> dir;
			float rot = 0.0f;

			if (Soon::Input::GetKeyDown(GLFW_KEY_W))
				dir.z += 0.01f;
			if (Soon::Input::GetKeyDown(GLFW_KEY_S))
				dir.z -= 0.01f;
			if (Soon::Input::GetKeyDown(GLFW_KEY_A))
				dir.x -= 0.01f;
			if (Soon::Input::GetKeyDown(GLFW_KEY_D))
				dir.x += 0.01f;
			if (Soon::Input::GetKeyDown(GLFW_KEY_SPACE))
				dir.y += 0.01f;
			if (Soon::Input::GetKeyDown(GLFW_KEY_LEFT_CONTROL))
				dir.y -= 0.01f;
			if (Soon::Input::GetKeyDown(GLFW_KEY_LEFT))
				rot = 1.0f;
			if (Soon::Input::GetKeyDown(GLFW_KEY_RIGHT))
				rot = -1.0f;

			for (Entity& entity : entities)
			{
				entity.GetComponent<Transform3D>().Translate(dir);
				entity.GetComponent<Transform3D>().Rotate(0.0f, rot, 0.0f);
			}
		}
};
