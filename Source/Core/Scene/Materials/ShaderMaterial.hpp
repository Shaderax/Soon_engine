#pragma once

#include "Core/Renderer/Pipelines/ShaderPipeline.hpp"
#include "Core/Scene//Materials/Material.hpp"

#include "Core/Renderer/Vulkan/GraphicsRenderer.hpp"

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
