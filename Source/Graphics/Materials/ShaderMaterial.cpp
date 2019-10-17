#include "Graphics/Pipelines/DefaultPipeline.hpp"
#include "Graphics/Materials/ShaderMaterial.hpp"

namespace Soon
{
	ShaderMaterial::ShaderMaterial( void )
	{
		SetPipeline<DefaultPipeline>();
	}
}
