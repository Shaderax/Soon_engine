#pragma once

#include "Graphics/Pipelines/BasePipeline.hpp"
#include "Scene/3D/Components/Transform3D.hpp"

namespace Soon
{
	class Mesh;
	
	class ShaderPipeline : public BasePipeline
	{
		public:
			ShaderPipeline()
			{
				_type = PipelineType::GRAPHIC;
			}

			virtual void AddToRender( Transform3D& tr, Mesh* mesh ) = 0;
	};
}
