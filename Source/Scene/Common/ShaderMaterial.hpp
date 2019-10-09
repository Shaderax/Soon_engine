#pragma once

namespace Soon
{
	class ShaderMaterial : Material
	{
		public:
			ShaderPipeline*		_shaderPipeline;

			template<class T>
				void SetPipeline( void )
				{
					if (_shaderPipeline)
						_shaderPipeline->RemoveFromPipeline();
					_shaderPipeline = GraphicRenderer::GetInstance().AddPipeline<T>();
				}

	};
}
