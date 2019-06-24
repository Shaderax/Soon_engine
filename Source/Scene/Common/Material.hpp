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

//	Material& operator=(const Material& other)
//	{
//    	if (this == &other)
//			return *this;
//		_ambient = other._ambient;
//		_diffuse = other._diffuse;
//		_specular = other._specular;
//		_shininess = other._shininess;
//		_texture = other._texture;
//		return (*this);
//	}

	BasePipeline* _bpipeline;
	BasePipeline::Properties* _properties;
};
