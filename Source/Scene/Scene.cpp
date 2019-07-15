#include "Scene.hpp"

namespace Soon
{
	Scene::Scene( void )
	{

	}

	bool Scene::IsObjectInScene( Object& obj )
	{
		return (obj._scene == this ? true : false);
	}

	void Scene::AddObject( Object* parent, Object* obj )
	{
		if (parent)
		{
			if (parent->_scene != this)
				std::cout << "Parent Not in Scene" << std::endl;
			else
			{
				parent->_childrens.push_back(obj);
				obj->_scene = this;
				obj->_parent = parent;
			}
		}
		else
		{
			obj->_scene = this;
			Root.push_back(obj);
		}
	}

	Camera3D* Scene::GetCurrentCamera( void )
	{
		return (_camera);
	}

	void Scene::SetCurrentCamera( Camera3D* cam )
	{
		_camera = cam;
	}

}
