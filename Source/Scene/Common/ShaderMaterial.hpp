#pragma once

#include "Graphics/Pipelines/ShaderPipeline.hpp"
#include "Scene/Common/Material.hpp"

#include "Graphics/Vulkan/GraphicsRenderer.hpp"

namespace Soon
{
	class ShaderMaterial : public Material
	{
		public:
			ShaderPipeline*		_shaderPipeline;

			template<class T>
				void SetPipeline( void )
				{
					if (_shaderPipeline)
						_shaderPipeline->RemoveFromPipeline();
					_shaderPipeline = GraphicRenderer::GetInstance().AddPipeline<T>();
				}

	};
}
