#pragma once

#include "Core/Renderer/Pipelines/BasePipeline.hpp"
#include "Core/Scene/3D/Components/Transform3D.hpp"

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

			virtual void AddToRender( Transform3D& transform, Mesh* mesh ) = 0;
	};
}
