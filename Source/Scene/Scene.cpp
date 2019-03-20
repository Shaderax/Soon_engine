#include "Scene.hpp"

namespace Soon
{
	bool Scene::ObjectInScene( Object& obj )
	{
		return (obj.parent == this ? true : false);
	}

	Object& Scene::AddObjectInScene( Object& obj )
	{
		obj._scene = this;
		obj._parent = nullptr;
		Tree.push_back(obj);
		Tree.back().push_back(obj._childs);
	}

	void Scene::AddObjectInScene( Object* parent, Object& obj )
	{
		if (parent)
		{
			if (parent->_scene != this)
				std::cout << "Parent Not in Scene" << std::endl;
			else
			{
				obj._scene = this;
				obj._parent = parent;
				Tree.push_back(obj);
				Tree.back().push_back(obj._childs);
			}
		}
	}

	Object& Scene::NewObjectInScene( void )
	{
		Object* obj = new Object();

		obj->_scene = this;
		obj->_parent = nullptr;

		Tree.push_back(obj);
		
		return *(obj);
	}
}
