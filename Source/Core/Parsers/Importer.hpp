#pragma once

#include <string>

namespace Soon
{
	struct Importer
	{
		template<class T>
		T import( std::string path ) { std::cout << "Je suis la fonction Import de base !" << std::endl;};
	};
}
