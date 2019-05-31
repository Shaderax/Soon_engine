#include "Graphics/Vulkan/GraphicsRenderer.hpp"
#include "Graphics/Vulkan/GraphicsInstance.hpp"
#include "Scene/3D/Components/Transform3D.hpp"

namespace Soon
{
		GraphicsRenderer* GraphicsRenderer::_instance = nullptr;

		GraphicsRenderer* GraphicsRenderer::GetInstance( void )
		{
			return (_instance);
		}

		void GraphicsRenderer::Initialize( void )
		{
			_uniformCamera = GraphicsInstance::GetInstance()->CreateUniform(sizeof(UniformCamera), 0);
		}

		GraphicsRenderer::GraphicsRenderer( void ) : _changes(false)
		{
			_instance = this;
		}

		ComponentRenderer GraphicsRenderer::AddToRender( Transform3D& tr, VertexBufferInfo inf)
		{
			BufferRenderer handler;
			ComponentRenderer ret;

			handler = GraphicsInstance::GetInstance()->CreateVertexBuffer(inf);
			std::cout << "VkBuffer in AddToRender : " << handler._Buffer[0] << std::endl;

			_nbVertex.push_back(inf._nbVertex);
			_transforms.push_back(&tr);
			_vkBuffers.push_back(handler._Buffer[0]);
			_vkDevicesMemoryBuffers.push_back(handler._BufferMemory[0]);

			ret._transform = _transforms.end();
			ret._vkBuffers = _vkBuffers.end();
			ret._vkDevicesMemoryBuffers = _vkDevicesMemoryBuffers.end();

			///////////// UNIFORM /////////////

			UniformSets modelUniform = GraphicsInstance::GetInstance()->CreateUniform(sizeof(UniformModel));			

			_uniformsBuffers.push_back(modelUniform._uniformRender);
			_uniformsDescriptorSets.push_back(modelUniform._descriptorSets);

			///////////////////////////////////

			_changes = true;
			return ret;
		}

		std::vector< VkBuffer > GraphicsRenderer::GetvkBuffers( void )
		{
			return (_vkBuffers);
		}

		std::vector< uint32_t > GraphicsRenderer::GetNbVertex( void )
		{
			return (_nbVertex);
		}

		bool GraphicsRenderer::HasChange( void )
		{
			return (_changes);
		}

		void GraphicsRenderer::SetChangeFalse( void )
		{
			_changes = false;
		}

		std::vector< Transform3D* > GraphicsRenderer::GetTransforms( void )
		{
			return (_transforms);
		}

		std::vector< BufferRenderer > GraphicsRenderer::GetUniformBuffers( void )
		{
			return (_uniformsBuffers);
		}

		UniformSets GraphicsRenderer::GetUniformsCamera( void )
		{
			return (_uniformCamera);
		}

		std::vector< std::vector<VkDescriptorSet> > GraphicsRenderer::GetUniformsDescriptorSets( void )
		{
			return (_uniformsDescriptorSets);
		}

		std::vector<VkDescriptorSet> GraphicsRenderer::GetUniformCameraDescriptorSets( void )
		{
			return (_uniformCamera._descriptorSets);
		}
}
