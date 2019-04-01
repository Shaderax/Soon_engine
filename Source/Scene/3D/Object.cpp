#include "Object.hpp"
#include "Transform.hpp"

namespace Soon
{
	Object::Object( void )
	{
		_transform = AddComponent<Transform>();
	}
}
