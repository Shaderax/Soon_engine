#include "Core/Pipelines/DefaultPipeline.hpp"
#include "Core/Scene/Materials/ShaderMaterial.hpp"

namespace Soon
{
	ShaderMaterial::ShaderMaterial( void )
	{
		_shaderPipeline = nullptr;
		SetPipeline<DefaultPipeline>();
	}

	ShaderMaterial::~ShaderMaterial( void )
	{
		Destroy();
	}

	void ShaderMaterial::Render( Transform3D& tr, Mesh* mesh )
	{
		if (_shaderPipeline)
			_id = _shaderPipeline->AddToRender(tr, mesh);
	}

	void ShaderMaterial::Unrender( void )
	{

	}

	void ShaderMaterial::Destroy( void )
	{
		if (_shaderPipeline)
			_shaderPipeline->RemoveFromPipeline(_id);
		_shaderPipeline = nullptr;
	}
}
