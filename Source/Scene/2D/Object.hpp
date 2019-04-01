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

			Transform&	_transform;

			Scene*		_scene;

			friend Scene;
	};
}
