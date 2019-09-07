#pragma once

#include <string>

namespace Soon
{
	struct Importer
	{
		template<class T>
		T import( std::string path );
	};
}
