#pragma once

#include "Scene/Common/Texture.hpp"

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

		void SetTexture( std::string name, Texture& texture )
		{

		}

		void SetFloat( std::string name, float value )
		{

		}

		void SetVec3( std::string name, vec3<float> vec )
		{
			
		}

//		BasePipeline*				_bpipeline;
	};
}
