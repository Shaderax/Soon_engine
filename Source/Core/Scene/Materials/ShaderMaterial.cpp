#include "Core/Pipelines/DefaultPipeline.hpp"
#include "Core/Scene/Materials/ShaderMaterial.hpp"

namespace Soon
{
	ShaderMaterial::ShaderMaterial( void )
	{
		SetPipeline<DefaultPipeline>();
	}
}
