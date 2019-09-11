#pragma once

#include "Scene/3D/Components/Mesh.hpp"
#include <list>

namespace Soon
{
	class MeshArray
	{
		public:
			std::list<Mesh> _meshArray;

			  MeshArray& operator+=(const MeshArray& rhs)
			  {
				  _meshArray.insert(_meshArray.end(), rhs._meshArray.begin(), rhs._meshArray.end());

				  return (*this);
			  }

			  MeshArray& operator=(const MeshArray& rhs)
			  {
				  _meshArray = rhs._meshArray;

				  return (*this);
			  }
	};
};
