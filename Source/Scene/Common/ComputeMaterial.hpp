#pragma once

#include "Graphics/Pipelines/ComputePipeline.hpp"
#include "Scene/Common/Material.hpp"

#include "Graphics/Vulkan/GraphicsRenderer.hpp"

namespace Soon
{
	class ComputeMaterial : public Material
	{
		public:
			ComputePipeline*	_computePipeline;

			template<class T>
				void SetPipeline( void )
				{
					if (_computePipeline)
						_computePipeline->RemoveFromPipeline();
					_computePipeline = GraphicsRenderer::GetInstance()->AddPipeline<T>();
				}
	};
}
