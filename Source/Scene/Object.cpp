#include "Object.hpp"
#include "Core/Engine.hpp"
#include "Scene/3D/Components/Transform3D.hpp"
#include "Scene/Common/ObjectOwner.hpp"

namespace Soon
{
	Object::Object( Object* parent )
	{
		AddComponent<Transform3D>();
		AddComponent<ObjectOwner>(this);

		if (Engine::GetInstance().GetCurrentScene())
			Engine::GetInstance().GetCurrentScene()->AddObject(parent, this);
	}
	
	Object::~Object( void )
	{
		Kill();
	}
}
