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
			_uniformCamera = GraphicsInstance::GetInstance()->CreateUniform(sizeof(UniformCamera), DescriptorTypeLayout::CAMERA);
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

			UniformSets modelUniform = GraphicsInstance::GetInstance()->CreateUniform(sizeof(UniformModel), DescriptorTypeLayout::MODEL);

			_uniformsBuffers.push_back(modelUniform._uniformRender);
			_uniformsDescriptorSets.push_back(modelUniform._descriptorSets);

			///////////// TEXTURE ////////////

			Image img;

			std::cout << inf._material->_texture._width << " " << inf._material->_texture._height << std::endl;
			_imagesRenderer.push_back(GraphicsInstance::GetInstance()->CreateTextureImage(&(inf._material->_texture)));
			img._textureSampler = GraphicsInstance::GetInstance()->CreateTextureSampler();
			img._imageView = GraphicsInstance::GetInstance()->CreateImageView(_imagesRenderer.back()._textureImage, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_ASPECT_COLOR_BIT);
			_images.push_back(img);

			std::vector<VkDescriptorSet> imageUniform = GraphicsInstance::GetInstance()->CreateImageDescriptorSets(img._imageView, img._textureSampler);
			_uniformsImagesDescriptorSets.push_back(imageUniform);

			/////////// MATERIAL //////////////

			UniformSets matUniform = GraphicsInstance::GetInstance()->CreateUniform(sizeof(UniformMaterial), DescriptorTypeLayout::MATERIAL);

			_uniformsMaterials.push_back(matUniform._uniformRender);
			_uniformsMaterialsDescriptorSets.push_back(matUniform._descriptorSets);
			_vecMaterials.push_back(inf._material);

			std::cout << GetMaterials().at(0)->_ambient.x << std::endl;

			/////////////////

			_changes = true;
			return ret;
		}
		
		void GraphicsRenderer::AddLightToRender( Transform3D& tr, DirectionalLight* dl)
		{
			std::cout << "EZ : " << GetMaterials().at(0)->_ambient.x << std::endl;
			UniformSets lightUniform = GraphicsInstance::GetInstance()->CreateUniform(sizeof(UniformLight), DescriptorTypeLayout::LIGHT);

			_uniformsLights.push_back(lightUniform._uniformRender);
			_uniformsLightsDescriptorSets.push_back(lightUniform._descriptorSets);

			_vecLights.push_back(dl);
		}

		void GraphicsRenderer::RecreateAllUniforms( void )
		{
			_uniformCamera = GraphicsInstance::GetInstance()->CreateUniform(sizeof(UniformCamera), DescriptorTypeLayout::CAMERA);

			int j = -1;
			while (++j < _uniformsBuffers.size())
			{
				UniformSets modelUniform = GraphicsInstance::GetInstance()->CreateUniform(sizeof(UniformModel), DescriptorTypeLayout::MODEL);
				_uniformsBuffers.at(j) = modelUniform._uniformRender;
				_uniformsDescriptorSets.at(j) = modelUniform._descriptorSets;
			}
			j = -1;
			while (++j < _uniformsImagesDescriptorSets.size())
			{
				std::vector<VkDescriptorSet> imageUniform = GraphicsInstance::GetInstance()->CreateImageDescriptorSets(_images.at(j)._imageView, _images.at(j)._textureSampler);
				_uniformsImagesDescriptorSets.at(j) = imageUniform;
			}

			/// RECREATE MATERIALS
			j = -1;
			while (++j < _uniformsMaterialsDescriptorSets.size())
			{
				UniformSets matUniform = GraphicsInstance::GetInstance()->CreateUniform(sizeof(UniformMaterial), DescriptorTypeLayout::MATERIAL);
				_uniformsMaterials.at(j) = matUniform._uniformRender;
				_uniformsMaterialsDescriptorSets.at(j) = matUniform._descriptorSets;
			}

			///// RECREATE LIGHTS
			j = -1;
			while (++j < _vecLights.size())
			{
				UniformSets lightUniform = GraphicsInstance::GetInstance()->CreateUniform(sizeof(UniformLight), DescriptorTypeLayout::LIGHT);
				_uniformsLights.at(j) = lightUniform._uniformRender;
				_uniformsLightsDescriptorSets.at(j) = lightUniform._descriptorSets;
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

		std::vector< std::vector<VkDescriptorSet> > GraphicsRenderer::GetUniformsMaterialsDescriptorSets( void )
		{
			return _uniformsMaterialsDescriptorSets;
		}

		std::vector< BufferRenderer > GraphicsRenderer::GetUniformsMaterials( void )
		{
			return _uniformsMaterials;
		}

		std::vector< Material * > GraphicsRenderer::GetMaterials( void )
		{
			return (_vecMaterials);
		}

		std::vector< std::vector<VkDescriptorSet> > GraphicsRenderer::GetUniformsLightsDescriptorSets( void )
		{
			return _uniformsLightsDescriptorSets;
		}

		std::vector< BufferRenderer > GraphicsRenderer::GetUniformsLights( void )
		{
			return _uniformsLights;
		}

		std::vector< DirectionalLight * > GraphicsRenderer::GetLights( void )
		{
			return (_vecLights);
		}
}
