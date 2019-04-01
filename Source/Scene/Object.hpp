#pragma once

namespace Soon
{
	class Object : public Entity
	{
		public:
			Object( void );
			~Object( void );
		private:
			Object*					_parent;
			std::vector<Object&>	_childs

			Scene*		_scene;

			friend Scene;
	};
}
