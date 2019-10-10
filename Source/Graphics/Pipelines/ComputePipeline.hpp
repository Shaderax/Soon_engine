#pragma once

#include "Graphics/Pipelines/BasePipeline.hpp"

namespace Soon
{
	class Mesh;

	class ComputePipeline : public BasePipeline
	{
		public:
			ComputePipeline()
			{
			_type = PipelineType::COMPUTE;
			}
			virtual void AddToRender( Mesh* mesh, uint32_t amount ) = 0;
	};
}
