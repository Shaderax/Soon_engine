#pragma once

#include "Graphics/Pipelines/BasePipeline.hpp"

namespace Soon
{
	class Mesh;

	class ComputePipeline : public BasePipeline
	{
		public:
		static const PipelineType _type = PipelineType::COMPUTE;
			ComputePipeline()
			{
			}
			virtual void AddToRender( Mesh* mesh, uint32_t amount ) = 0;
	};
}
