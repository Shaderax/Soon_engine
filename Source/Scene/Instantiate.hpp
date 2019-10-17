#pragma once

#include <list>
#include "Object.hpp"
#include "Utilities/MeshArray.hpp"

namespace Soon
{
	Object* Instantiate( MeshArray meshArray, Object* parent = nullptr)
	{
		Object* folder = new Object(parent);
		for (Mesh& mesh : meshArray._meshArray)
		{
			Texture* tt = mesh._material.GetTexture("texSampler");

			Object* obj = new Object(folder);
			Mesh& me = obj->AddComponent<Soon::Mesh>(mesh);
			me.EnableRender();
		}
		return folder;
	}
}

// Try without template
