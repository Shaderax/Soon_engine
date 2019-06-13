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
			_uniformCamera = GraphicsInstance::GetInstance()->CreateUniform(sizeof(UniformCamera));
		}

		GraphicsRenderer::GraphicsRenderer( void ) : _changes(false)
		{
			_instance = this;
		}

		ComponentRenderer GraphicsRenderer::AddToRender( Transform3D& tr, VertexBufferInfo inf)
		{
			std::vector<BufferRenderer> handler = GraphicsInstance::GetInstance()->CreateVertexBuffer(inf);
			ComponentRenderer ret;

			_stagingBuffers.push_back(handler[0]);
			_gpuBuffers.push_back(handler[1]._Buffer[0]);
			_gpuMemoryBuffers.push_back(handler[1]._BufferMemory[0]);

			_indexBuffers.push_back(GraphicsInstance::GetInstance()->CreateIndexBuffer(inf));

			_nbVertex.push_back(inf._nbVertex);
			_indexSize.push_back(inf._indexSize);
			_transforms.push_back(&tr);

			ret._transform = _transforms.end();
			ret._vkBuffers = _gpuBuffers.end();
			ret._vkDevicesMemoryBuffers = _gpuMemoryBuffers.end();

			///////////// UNIFORM /////////////

			UniformSets modelUniform = GraphicsInstance::GetInstance()->CreateUniform(sizeof(UniformModel));			

			_uniformsBuffers.push_back(modelUniform._uniformRender);
			_uniformsDescriptorSets.push_back(modelUniform._descriptorSets);

			///////////// TEXTURE ////////////

			std::cout << inf._material->_texture._width << " " << inf._material->_texture._height << std::endl;
			_imagesRenderer.push_back(GraphicsInstance::GetInstance()->CreateTextureImage(&(inf._material->_texture)));
			VkSampler textureSampler = GraphicsInstance::GetInstance()->CreateTextureSampler();
			VkImageView imageView = GraphicsInstance::GetInstance()->CreateImageView(_imagesRenderer.back()._textureImage, VK_FORMAT_R8G8B8A8_UNORM);
			UniformSets imageUniform = GraphicsInstance::GetInstance()->CreateImageDescriptorSets(imageView, textureSampler);
			_uniformsImagesDescriptorSets.push_back(imageUniform._descriptorSets);


			_changes = true;
			return ret;
		}

		void GraphicsRenderer::RecreateAllUniforms( void )
		{
			_uniformCamera = GraphicsInstance::GetInstance()->CreateUniform(sizeof(UniformCamera));

			int j = -1;
			while (++j < _uniformsBuffers.size())
			{
				UniformSets modelUniform = GraphicsInstance::GetInstance()->CreateUniform(sizeof(UniformModel));			
				_uniformsBuffers.at(j) = modelUniform._uniformRender;
				_uniformsDescriptorSets.at(j) = modelUniform._descriptorSets;
			}
		}

		std::vector< VkBuffer > GraphicsRenderer::GetvkBuffers( void )
		{
			return (_gpuBuffers);
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
		
		std::vector< VkDeviceMemory >   GraphicsRenderer::GetVkDeviceMemory( void )
		{
			return (_gpuMemoryBuffers);
		}

		std::vector< BufferRenderer >   GraphicsRenderer::GetIndexBuffers( void )
		{
			return (_indexBuffers);
		}

		std::vector<uint32_t>			GraphicsRenderer::GetIndexSize( void )
		{
			return (_indexSize);
		}

		std::vector< std::vector<VkDescriptorSet> > GraphicsRenderer::GetUniformsImagesDescriptorSets( void )
		{
			return (_uniformsImagesDescriptorSets);
		}
}
