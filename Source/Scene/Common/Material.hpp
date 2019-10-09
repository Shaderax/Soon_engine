#pragma once

#include "Graphics/Pipelines/BasePipeline.hpp"

namespace Soon
{
	struct Material
	{
		Material( void )
		{

		}

		virtual ~Material( void )
		{

		}

//		template<class T>
//		void SetPipeline( void )
//		{
//			if (_bpipeline)
//				_bpipeline->RemoveFromPipeline();
//			_bpipeline = GraphicRenderer::GetInstance().AddPipeline<T>();
//		}

		void SetTexture( std::string name, Texture* texture )
		{

		}

//		BasePipeline*				_bpipeline;
	};
}
