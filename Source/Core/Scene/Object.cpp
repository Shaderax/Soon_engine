#include "Core/Scene/Object.hpp"
#include "Core/Engine.hpp"
#include "Core/Scene/3D/Components/Transform3D.hpp"

namespace Soon
{
	Object::Object( Object* parent )
	{
		AddComponent<Transform3D>();

		if (Engine::GetInstance().GetCurrentScene())
			Engine::GetInstance().GetCurrentScene()->AddObject(parent, this);
	}
	
	Object::~Object( void )
	{
		if (_scene && !_parent)
			_scene->RemoveObject(this);

		for (Object* child : _childrens)
			delete child;

		Kill();
	}

	std::vector< Object* >& Object::GetChildrens( void )
	{
		return (_childrens);
	}
}
