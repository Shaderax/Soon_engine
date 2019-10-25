#pragma once

#include "ECS/Entity.hpp"
#include <vector>

namespace Soon
{
	class Scene;

	class Object : public Entity
	{
		public:
			Object( Object* parent = nullptr );
			~Object( void );
			std::vector< Object* >& GetChildrens( void );
		private:
			Object*					_parent;
			std::vector<Object*>	_childrens;

			Scene*		_scene;

			friend Scene;
	};
}
