#pragma once

#include "Graphics/Pipelines/BasePipeline.hpp"

namespace Soon
{
	struct Material
	{
		Material( void )
		{

		}

		~Material( void )
		{

		}

		template<class T>
		void SetPipeline( void )
		{
			if (_bpipeline)
				_bpipeline->RemoveFromPipeline();
			_bpipeline = GraphicRenderer::GetInstance().AddPipeline<T>();
			_properties = new T::Properties();
		}

		BasePipeline*				_bpipeline;
		BasePipeline::Properties*	_properties;
	};
}

/*
	Que veux tu pour les pipelines

	ComponentRenderer { Material material }

	Mesh : ComponentRenderer
	{
		EnableRender( void )
		{
			GraphicRenderer::AddToRender(this, material);
		}
	}












	 ou alors c'est au moment du AddPipeline que je fais le AddTorender





*/
