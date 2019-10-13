#include "Graphics/Vulkan/GraphicsRenderer.hpp"
#include "Graphics/Vulkan/GraphicsInstance.hpp"
#include "Scene/3D/Components/Transform3D.hpp"
#include "Graphics/Pipelines/SkyboxPipeline.hpp"
#include <typeinfo>
#include "ECS/ClassTypeId.hpp"

#include "Graphics/Pipelines/BasePipeline.hpp"
#include "Graphics/Pipelines/ShaderPipeline.hpp"
#include "Graphics/Pipelines/ComputePipeline.hpp"


namespace Soon
{
	GraphicsRenderer* GraphicsRenderer::_instance = nullptr;

	GraphicsRenderer* GraphicsRenderer::GetInstance( void )
	{
		return (_instance);
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
		AddPipeline<SkyboxPipeline>();
	}

	GraphicsRenderer::GraphicsRenderer( void ) : _changes(false)
	{
		_instance = this;
	}

	void GraphicsRenderer::AddLight( Transform3D& tr, Light* light)
	{
		//		DefaultVertexPipeline* pip = reinterpret_cast<DefaultVertexPipeline*>(_graphicPipelines[ClassTypeId<BasePipeline>::GetId<DefaultVertexPipeline>()]);
		//		pip->AddLightToRender(tr, dl);
		_lights.push_back(light);

		_changes = true;
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

	bool GraphicsRenderer::HasChange( void )
	{
		return (_changes);
	}

	void GraphicsRenderer::SetChangeFalse( void )
	{
		_changes = false;
	}
};
