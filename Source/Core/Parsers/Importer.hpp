#pragma once

#include <string>

namespace Soon
{
	struct Importer
	{
		virtual uint32_t IdValidType( void ) = 0;
		virtual bool import( std::string path ) = 0;
	};
}
