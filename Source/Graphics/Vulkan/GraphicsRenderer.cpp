#include "Graphics/Vulkan/GraphicsRenderer.hpp"
#include "Graphics/Vulkan/GraphicsInstance.hpp"
#include "Scene/3D/Components/Transform3D.hpp"
#include "Graphics/Pipelines/DefaultPipeline.hpp"
#include "Graphics/Pipelines/DefaultVertexPipeline.hpp"
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
		void GraphicsRenderer::AddPipeline( void )
		{
			if (typeid(T) == typeid(DefaultPipeline) && _pipelines.size() == 0)
				_isDefault = true;
			else if (typeid(T) != typeid(DefaultPipeline) && _pipelines.size() == 1 && _isDefault == true)
			{
				_createdPipeline[ClassTypeId<BasePipeline>::GetId<DefaultPipeline>()] = false;
				delete _pipelines[ClassTypeId<BasePipeline>::GetId<DefaultPipeline>()];
				_pipelines[ClassTypeId<BasePipeline>::GetId<DefaultPipeline>()] = nullptr;
				_isDefault = false;
			}

			T* pipeline = new T;
			_pipelines[ClassTypeId<BasePipeline>::GetId<T>()] = pipeline;
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
			DefaultVertexPipeline* pip = reinterpret_cast<DefaultVertexPipeline*>(_pipelines[ClassTypeId<BasePipeline>::GetId<DefaultVertexPipeline>()]);
			pip->AddToRender(tr, inf);
			
			_changes = true;
		}
		
		void GraphicsRenderer::AddLightToRender( Transform3D& tr, DirectionalLight* dl)
		{
			DefaultVertexPipeline* pip = reinterpret_cast<DefaultVertexPipeline*>(_pipelines[ClassTypeId<BasePipeline>::GetId<DefaultVertexPipeline>()]);
			pip->AddLightToRender(tr, dl);
		}

//		void GraphicsRenderer::AddParticlesSystemToRender( Transform3D& tr, ParticlesSystem* ps )
//		{
//			
//		}

		void GraphicsRenderer::RecreateAllUniforms( void )
		{
			for (BasePipeline* bp : _pipelines)
				bp->RecreateUniforms();
		}

		void GraphicsRenderer::UpdateAllDatas( uint32_t imageIndex )
		{
			for (BasePipeline* bp : _pipelines)
				bp->UpdateData(imageIndex);
		}

		void GraphicsRenderer::PipelinesBindCaller( VkCommandBuffer commandBuffer, uint32_t index )
		{
			for (BasePipeline* bp : _pipelines)
			{
				std::cout << "OGOOGIGIYGUGUGUGUUGUGUUGUGU" << std::endl;
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
