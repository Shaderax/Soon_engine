#pragma once

namespace Soon
{
	Load3dObj( std::string path )
	{
		
	}

	template<class T>
	std::vector<T> Loader(std::string path)
	{
		std::vector<T> ret;

		if(path.substr(path.find_last_of(".") + 1) == "obj")
		{
			std::cout << "Loading obj file" << std:endl;
			Load3dObj(path);
		}
		else
			std::cout << "Error : Wut kind of template is that ?" << std::endl;

		return (ret);
	}
}
