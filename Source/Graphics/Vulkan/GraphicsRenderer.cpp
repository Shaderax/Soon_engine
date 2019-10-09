#include "Graphics/Vulkan/GraphicsRenderer.hpp"
#include "Graphics/Vulkan/GraphicsInstance.hpp"
#include "Scene/3D/Components/Transform3D.hpp"
#include "Graphics/Pipelines/DefaultPipeline.hpp"
#include "Graphics/Pipelines/DefaultVertexPipeline.hpp"
#include "Graphics/Pipelines/DefaultParticlesSystem.hpp"
#include "Graphics/Pipelines/DefaultComputeParticlesSystem.hpp"
#include <typeinfo>
#include "ECS/ClassTypeId.hpp"


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

	template<typename T, typename ... Args>
		T* GraphicsRenderer::AddPipeline( Args ... args )
		{
			if (_createdPipeline[ClassTypeId<BasePipeline>::GetId<T>()] == true)
			{
				if (T::_type == PipelineType::COMPUTE)
					return (_computePipelines[ClassTypeId<BasePipeline>::GetId<T>()]);
				else if (T::_type == PipelineType::GRAPHIC)
					return (_graphicPipelines[ClassTypeId<BasePipeline>::GetId<T>()]);
			}
			T* pipeline;
			pipeline = new T(std::forward<Args>(args) ...);
			if (T::_type == PipelineType::COMPUTE)
				_computePipelines[ClassTypeId<BasePipeline>::GetId<T>()] = pipeline;
			else if (T::_type == PipelineType::GRAPHIC)
				_graphicPipelines[ClassTypeId<BasePipeline>::GetId<T>()] = pipeline;

			_createdPipeline[ClassTypeId<BasePipeline>::GetId<T>()] = true;
			_changes = true;

			return (pipeline);
		}

	void GraphicsRenderer::Initialize( void )
	{
		AddPipeline<DefaultPipeline>();
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

//	void GraphicsRenderer::AddParticlesSystemToRender( Transform3D& tr, ParticlesSystem* ps )
//	{
//		if (!_createdPipeline[ClassTypeId<BasePipeline>::GetId<DefaultParticlesSystemPipeline>()])
//		{
//			AddPipeline<DefaultParticlesSystemPipeline>();
//			AddPipeline<DefaultComputeParticlesSystemPipeline>(reinterpret_cast<DefaultParticlesSystemPipeline*>(_graphicPipelines[ClassTypeId<BasePipeline>::GetId<DefaultParticlesSystemPipeline>()]));
//		}
//		DefaultParticlesSystemPipeline* pip = reinterpret_cast<DefaultParticlesSystemPipeline*>(_graphicPipelines[ClassTypeId<BasePipeline>::GetId<DefaultParticlesSystemPipeline>()]);
//		DefaultComputeParticlesSystemPipeline* cpsp = reinterpret_cast<DefaultComputeParticlesSystemPipeline*>(_computePipelines[ClassTypeId<BasePipeline>::GetId<DefaultComputeParticlesSystemPipeline>()]);
//		pip->AddToRender(tr, ps);
//		cpsp->AddToRender(tr, ps);
//
//		_changes = true;
//	}

	void GraphicsRenderer::RecreateAllUniforms( void )
	{
		for (BasePipeline* bp : _graphicPipelines)
			if (bp)
				bp->RecreateUniforms();
		for (BasePipeline* bp : _computePipelines)
			if (bp)
				bp->RecreateUniforms();
	}

	void GraphicsRenderer::RecreateAllPipelines( void )
	{
		for (BasePipeline* bp : _graphicPipelines)
			if (bp)
				bp->RecreatePipeline();
		for (BasePipeline* bp : _computePipelines)
			if (bp)
				bp->RecreatePipeline();
	}

	void GraphicsRenderer::UpdateAllDatas( uint32_t imageIndex )
	{
		for (BasePipeline* bp : _graphicPipelines)
			if (bp)
				bp->UpdateData(imageIndex);
		for (BasePipeline* bp : _computePipelines)
			if (bp)
				bp->UpdateData(imageIndex);
	}

	void GraphicsRenderer::GraphicPipelinesBindCaller( VkCommandBuffer commandBuffer, uint32_t index )
	{
		for (BasePipeline* bp : _graphicPipelines)
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
		for (BasePipeline* bp : _computePipelines)
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
