#include "Object.hpp"
#include "Scene/3D/Components/Transform3D.hpp"

namespace Soon
{
	Object::Object( void )
	{
		AddComponent<Transform3D>();
	}
	
	Object::~Object( void )
	{
	}
}
