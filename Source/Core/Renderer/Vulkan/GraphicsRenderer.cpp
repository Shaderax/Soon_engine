#include "GraphicsRenderer.hpp"
#include "GraphicsInstance.hpp"
#include <typeinfo>
#include "ClassTypeId.hpp"

#include "Core/Renderer/Pipelines/BasePipeline.hpp"
#include "Core/Renderer/Pipelines/ShaderPipeline.hpp"
#include "Core/Renderer/Pipelines/ComputePipeline.hpp"

#include <iostream>

namespace Soon
{
	//GraphicsRenderer* GraphicsRenderer::_instance = nullptr;

	GraphicsRenderer* GraphicsRenderer::GetInstance( void )
	{
		static GraphicsRenderer* instance = new GraphicsRenderer;

		return (instance);
		//return (_instance);
	}

	void GraphicsRenderer::Destroy( void )
	{

	}

	template<typename T>
		void GraphicsRenderer::RemovePipeline( void )
		{
			_createdPipeline[ClassTypeId<BasePipeline>::GetId<T>()] = false;
			delete _graphicPipelines[ClassTypeId<BasePipeline>::GetId<T>()];

			_graphicPipelines[ClassTypeId<BasePipeline>::GetId<T>()] = nullptr;
		}

	void GraphicsRenderer::Initialize( void )
	{
		for (ShaderPipeline* pip : _graphicPipelines)
			pip = nullptr;
		for (ComputePipeline* pip : _computePipelines)
			pip = nullptr;
//		AddPipeline<SkyboxPipeline>();
	}

	GraphicsRenderer::GraphicsRenderer( void ) : _changes(false)
	{
		//_instance = this;
	}

	void GraphicsRenderer::RecreateAllUniforms( void )
	{
		for (ShaderPipeline* bp : _graphicPipelines)
			if (bp)
				bp->RecreateUniforms();
		for (ComputePipeline* bp : _computePipelines)
			if (bp)
				bp->RecreateUniforms();
	}

	void GraphicsRenderer::RecreateAllPipelines( void )
	{
		for (ShaderPipeline* bp : _graphicPipelines)
			if (bp)
				bp->RecreatePipeline();
		for (ComputePipeline* bp : _computePipelines)
			if (bp)
				bp->RecreatePipeline();
	}

	void GraphicsRenderer::UpdateAllDatas( uint32_t imageIndex )
	{
		for (ShaderPipeline* bp : _graphicPipelines)
			if (bp)
				bp->UpdateData(imageIndex);
		for (ComputePipeline* bp : _computePipelines)
			if (bp)
				bp->UpdateData(imageIndex);
	}

	void GraphicsRenderer::GraphicPipelinesBindCaller( VkCommandBuffer commandBuffer, uint32_t index )
	{
		for (ShaderPipeline* bp : _graphicPipelines)
		{
			if (bp != nullptr)
			{
				std::cout << "Graphic Bind Caller" << std::endl;
				bp->BindCaller(commandBuffer, index );
			}
		}
		std::cout << std::endl;
	}

	void GraphicsRenderer::ComputePipelinesBindCaller( VkCommandBuffer commandBuffer, uint32_t index )
	{
		for (ComputePipeline* bp : _computePipelines)
		{
			if (bp)
			{
				std::cout << "Compute Bind Caller" << std::endl;
				bp->BindCaller(commandBuffer, index );
			}
		}
		std::cout << std::endl;
	}

	void GraphicsRenderer::HasChange( void )
	{
		_changes = true;
	}

	bool GraphicsRenderer::IsChange( void )
	{
		return (_changes);
	}

	void GraphicsRenderer::ResetChange( void )
	{
		_changes = false;
	}
};
