#pragma once

#include "Graphics/Pipelines/ShaderPipeline.hpp"
#include "Graphics/Materials/Material.hpp"

#include "Graphics/Vulkan/GraphicsRenderer.hpp"

namespace Soon
{
	class ShaderMaterial : public Material
	{
		public:
			ShaderPipeline*		_shaderPipeline = nullptr;

			ShaderMaterial( void );

			template<class T>
				void SetPipeline( void )
				{
					if (_shaderPipeline)
						_shaderPipeline->RemoveFromPipeline();
					_shaderPipeline = GraphicsRenderer::GetInstance()->AddPipeline<T>();
				}

	};
}
