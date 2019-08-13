#pragma once

#include "Importer.hpp"

namespace Soon
{
	class MeshImporter : Importer
	{
		MeshImporter( void ) {};
		~MeshImporter( void ) {};
		virtual void import( std::string path ) = 0;
		virtual void valid_extension( std::string ext ) = 0;
		virtual void valid_type( std::string ext ) = 0;
	};
}
