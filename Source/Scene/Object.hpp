#pragma once

#include "ECS/Entity.hpp"
#include <vector>

namespace Soon
{
	class Scene;

	class Object : public Entity
	{
		public:
			Object( void );
			~Object( void );
		private:
			Object*					_parent;
//			std::vector<Object&>	_childs;

			Scene*		_scene;

			friend Scene;
	};
}
