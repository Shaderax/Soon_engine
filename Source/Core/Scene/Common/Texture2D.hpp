#pragma once

#include "Core/Scene/Common/Texture.hpp"

struct Texture2D : Texture
{
	Texture2D( void )
	{
		_tType = TextureType::TEXTURE_2D;
	}

	~Texture2D( void )
	{

	}
};
