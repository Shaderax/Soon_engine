#pragma once
#include <stb/stb_image.h>
#include <cstring>
#include "Scene/Common/Texture.hpp"

std::array<char*, 6> files =
{
	"../Ressources/skybox/hw_lagoon/lagoon_bk.tga",
	"../Ressources/skybox/hw_lagoon/lagoon_rt.tga",
	"../Ressources/skybox/hw_lagoon/lagoon_dn.tga",
	"../Ressources/skybox/hw_lagoon/lagoon_ft.tga",
	"../Ressources/skybox/hw_lagoon/lagoon_up.tga",
	"../Ressources/skybox/hw_lagoon/lagoon_lf.tga"
};

struct TextureCubeMap : Texture
{
	TextureCubeMap( void ) : _tType(Texture_Type::TEXTURE_CUBE)
	{
		int format;
		unsigned char* tmp;
		bool first = true;

		for (int i = 0 ; i < 6 ; i++)
		{
			tmp = stbi_load(files[i], &_width, &_height, &format, STBI_rgb_alpha);
			if (!tmp)
				exit(0);

			std::cout << "Open Texture : " << files[i] << std::endl;
			std::cout << _width << " " << _height << std::endl;
			if (first)
			{
				_data = new unsigned char[6 * _width * _height * format];
				first = false;
			}
			strncat((char*)(&_data[i * _width * _height * format]), (const char*)tmp, _width * _height * format);
			stbi_image_free(tmp);
		}

		if (format == 0)
			_format = TEXTURE_FORMAT::UNDEFINED;
		else if (format == 1)
			_format = TEXTURE_FORMAT::G;
		else if (format == 2)
			_format = TEXTURE_FORMAT::GA;
		else if (format == 3)
			_format = TEXTURE_FORMAT::RGB;
		else if (format == 4)
			_format = TEXTURE_FORMAT::RGBA;
	}

	~TextureCubeMap( void )
	{

	}
};
