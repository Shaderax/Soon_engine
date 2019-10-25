#include "Core/Scene/3D/Components/Mesh.hpp"
#include <cstring>

namespace Soon
{
	void Mesh::EnableRender( void )
	{
		if (_owner && _material._shaderPipeline)
		{
			//std::cout << "Enable Render" << std::endl;
			_material._shaderPipeline->AddToRender(_owner->GetComponent<Transform3D>(), this);
		}
		else
		{
			//std::cout << "Can't Enable Render" << std::endl;
		}
		//		for (Object& obj : _owner.GetComponent<ObjectOwner>()._owner->GetChildrens())
		//			obj.EnableRender();
	}

	void Mesh::DisableRender( void )
	{
		//				if (_material._shaderPipeline)
		//					_material._shaderPipeline->RemoveRender();
	}
};
