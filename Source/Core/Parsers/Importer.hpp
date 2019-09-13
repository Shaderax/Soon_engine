#pragma once

#include <string>

namespace Soon
{
	struct Importer
	{
		uint32_t import( std::string path ) { std::cout << "Je suis la fonction Import de base !" << std::endl;};
	};
}
