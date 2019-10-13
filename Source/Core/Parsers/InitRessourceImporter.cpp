#include "Core/Parsers/RessourceImporter.hpp"
#include "Core/Parsers/MeshImporter.hpp"

namespace Soon
{
	void InitRessourceImporter( void )
	{
		RessourceImporter::GetSingleton().AddImporter<MeshImporter>();
	}
}
