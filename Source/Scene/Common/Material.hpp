#pragma once

#include "Scene/Common/Texture2D.hpp"
#include "Core/Math/vec3.hpp"

struct Material
{
	Material( void ) : _shininess(0.0f)
	{

	}

	~Material( void )
	{

	}

	Material& operator=(const Material& other)
	{
    	if (this == &other)
			return *this;
		_ambient = other._ambient;
		_diffuse = other._diffuse;
		_specular = other._specular;
		_shininess = other._shininess;
		_texture = other._texture;
		return (*this);
	}


	Texture2D _texture;
	vec3<float> _ambient;
	vec3<float> _diffuse;
	vec3<float> _specular;
	float		_shininess;
};
