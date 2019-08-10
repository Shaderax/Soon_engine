#pragma once

#include "ECS/ClassTypeId.hpp"

namespace Soon
{
	std::vector<Mesh> LoadMesh( std::string path )
	{
		
	}

	template<class T>
	std::vector<T> Loader(std::string path)
	{
		std::vector<T> ret;

		if (typeid(T) == typeid(Mesh))
		{
			std::cout << "Loading obj file" << std:endl;
			ret = LoadMesh(path);
		}
		else
			std::cout << "Error : Wut kind of template is that ?" << std::endl;

		return (ret);
	}
}




/*















*/
