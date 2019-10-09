#pragma once

namespace Soon
{
	class ComputePipeline : BasePipeline
	{
		public:
			ComputePipeline()
			{
			_type = PipelineType::COMPUTE;
			}
			virtual void AddToRender( Mesh* mesh, uint32_t amount ) = 0;
	};
}
