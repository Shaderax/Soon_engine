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
				Object* obj = new Object(folder);
				obj->AddComponent<Soon::Mesh>() = mesh;
			}
				return folder;
		}
}

// Try without template
