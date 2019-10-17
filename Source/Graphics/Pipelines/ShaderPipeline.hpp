#pragma once

#include "Graphics/Pipelines/BasePipeline.hpp"
#include "Scene/3D/Components/Transform3D.hpp"

namespace Soon
{
	class Mesh;
	
	class ShaderPipeline : public BasePipeline
	{
		public:
		static const PipelineType _type = PipelineType::GRAPHIC;

			ShaderPipeline()
			{
			}

			virtual void AddToRender( Transform3D& tr, Mesh* mesh ) = 0;
	};
}
