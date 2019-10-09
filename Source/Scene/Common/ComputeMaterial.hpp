#pragma once

namespace Soon
{
	class ComputeMaterial : Material
	{
		public:
			ComputePipeline*	_computePipeline;

			template<class T>
				void SetPipeline( void )
				{
					if (_computePipeline)
						_computePipeline->RemoveFromPipeline();
					_computePipeline = GraphicRenderer::GetInstance().AddPipeline<T>();
				}

	};
}
