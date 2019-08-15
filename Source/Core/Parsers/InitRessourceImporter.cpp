#include "Core/Parsers/RessourceImporter.hpp"
#include "Core/Parsers/MeshImporter.hpp"

namespace Soon
{
	bool InitRessourceImporter( void )
	{
		RessourceImporter::GetSingleton().AddImporter<MeshImporter>();
	}
}
