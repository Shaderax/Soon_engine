#pragma once

#include "RessourceMap.hpp"
#include "Importer.hpp"
#include "RessourceImporter.hpp"

namespace Soon
{
	class Texture2DImporter : public Importer
	{
		typedef Texture2D ValidType;
		public:
		std::string _path;
		Texture2DImporter( void ) { };
		~Texture2DImporter( void ) {};

		uint32_t IdValidType( void )
		{
			return (ClassTypeId<RessourceImporter>::GetId<ValidType>());
		}

		bool import( std::string path )
		{
			Texture2D texture;

			int format;
			texture._data = stbi_load(path.c_str(), &texture._width, &texture._height, &format, STBI_rgb_alpha);
			texture._format = TextureFormat::RGBA;
			if (texture._data)
			{
				std::cout << "Open Texture : " << path << std::endl;
				std::cout << texture._width << " " << texture._height << std::endl;
				std::cout << format << std::endl;
				// if (format == 0)
					//              _format = TextureFormat::UNDEFINED;
					//          else if (format == 1)
					//              _format = TextureFormat::G;
					//          else if (format == 2)
					//              _format = TextureFormat::GA;
					//          else if (format == 3)
					//              _format = TextureFormat::RGB;
					//          else if (format == 4)
					//              _format = TextureFormat::RGBA;
					//          stbi_image_free(data);
			}
			else
			{
				std::cout << "Texture2D failed to load at path: " << path << std::endl;
				stbi_image_free(texture._data);
				texture._data = stbi_load("../Ressources/texture/texture_oui.bmp", &texture._width, &texture._height, &format, 0);
				if (!texture._data)
					exit(-1);
			}

			GetRessourceMap<Texture2D>().emplace(std::make_pair(path, texture));

			return (true);
		}
	};
}
