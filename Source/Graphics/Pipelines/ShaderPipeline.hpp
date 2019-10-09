#pragma once

namespace Soon
{
	class ShaderPipeline : BasePipeline
	{
		public:
			ShaderPipeline()
			{
				_type = PipelineType::GRAPHIC;
			}
			virtual void AddToRender( Mesh* mesh ) = 0;
	};
}
