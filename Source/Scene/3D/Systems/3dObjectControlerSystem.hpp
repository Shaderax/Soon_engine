#include "ECS/System.hpp"
#include "Core/Math/vec3.hpp"

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

			for (Entity& entity : entities)
				entity.GetComponent<Transform3D>()._pos += dir;
		}
};
