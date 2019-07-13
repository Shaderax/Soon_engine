#pragma once

#include "Scene/Common/Texture2D.hpp"
#include "Core/Math/vec3.hpp"
#include "Graphics/Pipelines/BasePipeline.hpp"

struct Material
{
	Material( void )
	{

	}

	~Material( void )
	{

	}

	BasePipeline* _bpipeline;
	BasePipeline::Properties* _properties;
};
