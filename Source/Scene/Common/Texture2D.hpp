#pragma once
//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>
#include <stb/stb_image.h>

enum TEXTURE_FORMAT
{
	UNDEFINED,
	G,
	GA,
	RGB,
	RGBA
	//     N=#comp     components
	//     //       1           grey
	//     //       2           grey, alpha
	//     //       3           red, green, blue
	//     //       4           red, green, blue, alpha
};

struct Texture2D
{
	Texture2D( void )
	{

	}

	Texture2D( std::string path ) : _width(0), _height(0), _data(nullptr)
	{
		int format;
		_data = stbi_load(path.c_str(), &_width, &_height, &format, 0);
		if (_data)
		{
			std::cout << _width << " " << _height << std::endl;
			std::cout << "Open Texture : " << path << std::endl;
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
//			stbi_image_free(data);
		}
		else
		{
			std::cout << "Texture2D failed to load at path: " << path << std::endl;
			stbi_image_free(_data);
			_data = stbi_load("../Ressources/texture/texture_oui.bmp", &_width, &_height, &format, 0);
			if (!_data)
				exit(0);
		}
	}

	~Texture2D( void )
	{

	}

	unsigned char*		_data;
	int			_width;
	int			_height;
	TEXTURE_FORMAT		_format;

};
