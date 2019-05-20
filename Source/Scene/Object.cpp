#include "Object.hpp"
#include "Core/Engine.hpp"
#include "Scene/3D/Components/Transform3D.hpp"

namespace Soon
{
	Object::Object( Object* parent )
	{
		AddComponent<Transform3D>();

		if (Engine::GetInstance().GetCurrentScene())
			Engine::GetInstance().GetCurrentScene()->AddObject(parent, *this);
	}
	
	Object::~Object( void )
	{
	}
}
