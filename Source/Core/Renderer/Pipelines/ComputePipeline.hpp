#pragma once

#include "Core/Renderer/Pipelines/BasePipeline.hpp"
#include "Core/Scene/3D/Components/Transform3D.hpp"

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

			virtual uint32_t AddToPipeline( Transform3D& transform, Mesh* mesh, uint32_t amount ) = 0;
	};
}
