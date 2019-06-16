#pragma once

#include "Scene/Common/Texture2D.hpp"
#include "Core/Math/vec3.hpp"

struct Material
{
	Material( void )
	{

	}

	~Material( void )
	{

	}

	Texture2D _texture;
	vec3<float> _ambient;
	vec3<float> _diffuse;
	vec3<float> _specular;
	float		_shininess;
	//Shader  shader;
};
