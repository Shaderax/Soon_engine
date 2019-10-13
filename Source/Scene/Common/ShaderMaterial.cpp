#include "Graphics/Pipelines/DefaultPipeline.hpp"
#include "Scene/Common/ShaderMaterial.hpp"

namespace Soon
{
	ShaderMaterial::ShaderMaterial( void )
	{
		SetPipeline<DefaultPipeline>();
	}
}
