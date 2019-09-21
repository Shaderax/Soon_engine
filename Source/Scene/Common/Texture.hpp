#pragma once

#include <stb/stb_image.h>

enum TextureFormat
{
	UNDEFINED = 0,
	G = 1,
	GA = 2,
	RGB = 3,
	RGBA = 4
		//     N=#comp     components
		//     //       1           grey
		//     //       2           grey, alpha
		//     //       3           red, green, blue
		//     //       4           red, green, blue, alpha
};

enum TextureType
{
	TEXTURE_2D = 1,
	TEXTURE_CUBE = 6
};

struct Texture
{
	unsigned char*		_data;
	int			_width;
	int			_height;
	TextureFormat		_format;
	TextureType		_tType;
  
	Texture( void ) : _data(nullptr), _width(0), _height(0)
	{

	}

	~Texture( void )
	{
		stbi_image_free(_data);
	}

	Texture& operator=(const Texture& b)
	{
		if (this == &b)
			return *this;
		this->_data = b._data;
		this->_width = b._width;
		this->_height = b._height;
		this->_format = b._format;
		return *this;
	}
};
