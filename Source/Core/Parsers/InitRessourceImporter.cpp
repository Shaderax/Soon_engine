#include "Core/Parsers/RessourceImporter.hpp"
#include "Core/Parsers/MeshImporter.hpp"
#include "Core/Parsers/TextureImporter.hpp"

namespace Soon
{
	void InitRessourceImporter( void )
	{
		RessourceImporter::GetSingleton().AddImporter<MeshImporter>();
		RessourceImporter::GetSingleton().AddImporter<Texture2DImporter>();
	}
}
