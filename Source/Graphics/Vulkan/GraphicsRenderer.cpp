#include "Graphics/Vulkan/GraphicsRenderer.hpp"
#include "Graphics/Vulkan/GraphicsInstance.hpp"
#include "Scene/3D/Components/Transform3D.hpp"
#include "Graphics/Pipelines/DefaultPipeline.hpp"
#include "Graphics/Pipelines/DefaultVertexPipeline.hpp"
#include "Graphics/Pipelines/DefaultParticlesSystem.hpp"
#include <typeinfo>
#include "ECS/ClassTypeId.hpp"

namespace Soon
{
		GraphicsRenderer* GraphicsRenderer::_instance = nullptr;

		GraphicsRenderer* GraphicsRenderer::GetInstance( void )
		{
			return (_instance);
		}

		// TODO 
		// Max pipelines reach
		template<typename T>
		void GraphicsRenderer::AddPipeline( void )
		{
			if (typeid(T) == typeid(DefaultPipeline) && _graphicPipelines.size() == 0)
				_isDefault = true;
			else if (typeid(T) != typeid(DefaultPipeline) && _graphicPipelines.size() == 1 && _isDefault == true)
			{
				_createdPipeline[ClassTypeId<BasePipeline>::GetId<DefaultPipeline>()] = false;
				delete _graphicPipelines[ClassTypeId<BasePipeline>::GetId<DefaultPipeline>()];

				_graphicPipelines[ClassTypeId<BasePipeline>::GetId<DefaultPipeline>()] = nullptr;
				_isDefault = false;
			}

			T* pipeline = new T;
			if (typeid(T) == typeid(DefaultParticlesSystemPipeline))
				_computePipelines[ClassTypeId<BasePipeline>::GetId<T>()] = pipeline;
			else
				_graphicPipelines[ClassTypeId<BasePipeline>::GetId<T>()] = pipeline;
			_createdPipeline[ClassTypeId<BasePipeline>::GetId<T>()] = true;
			_changes = true;
		}

		void GraphicsRenderer::Initialize( void )
		{
			AddPipeline<DefaultPipeline>();
		}

		GraphicsRenderer::GraphicsRenderer( void ) : _changes(false), _isDefault(false)
		{
			_instance = this;
		}

		void GraphicsRenderer::AddVertexToRender( Transform3D& tr, VertexBufferInfo inf)
		{
			if (!_createdPipeline[ClassTypeId<BasePipeline>::GetId<DefaultVertexPipeline>()])
				AddPipeline<DefaultVertexPipeline>();
			DefaultVertexPipeline* pip = reinterpret_cast<DefaultVertexPipeline*>(_graphicPipelines[ClassTypeId<BasePipeline>::GetId<DefaultVertexPipeline>()]);
			pip->AddToRender(tr, inf);
			
			_changes = true;
		}
		
		void GraphicsRenderer::AddLightToRender( Transform3D& tr, DirectionalLight* dl)
		{
			DefaultVertexPipeline* pip = reinterpret_cast<DefaultVertexPipeline*>(_graphicPipelines[ClassTypeId<BasePipeline>::GetId<DefaultVertexPipeline>()]);
			pip->AddLightToRender(tr, dl);
			
			_changes = true;
		}

		void GraphicsRenderer::AddParticlesSystemToRender( Transform3D& tr, ParticlesSystem* ps )
		{
			if (!_createdPipeline[ClassTypeId<BasePipeline>::GetId<DefaultParticlesSystemPipeline>()])
				AddPipeline<DefaultParticlesSystemPipeline>();
			DefaultParticlesSystemPipeline* pip = reinterpret_cast<DefaultParticlesSystemPipeline*>(_computePipelines[ClassTypeId<BasePipeline>::GetId<DefaultParticlesSystemPipeline>()]);
			pip->AddToRender(tr, ps);
			
			_changes = true;
		}

		void GraphicsRenderer::RecreateAllUniforms( void )
		{
			for (BasePipeline* bp : _graphicPipelines)
				if (bp)
					bp->RecreateUniforms();
			for (BasePipeline* bp : _computePipelines)
				if (bp)
					bp->RecreateUniforms();
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
				if (bp)
					bp->BindCaller(commandBuffer, index );
			}
		}

		void GraphicsRenderer::ComputePipelinesBindCaller( VkCommandBuffer commandBuffer, uint32_t index )
		{
			for (BasePipeline* bp : _computePipelines)
			{
				if (bp)
					bp->BindCaller(commandBuffer, index );
			}
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
