#include "Graphics/Pipelines/BasePipeline.hpp"
#include "Graphics/Vulkan/GraphicsInstance.hpp"
#include "Core/Engine.hpp"
#include "Scene/3D/Components/Camera.hpp"
#include "Scene/Common/TextureCubeMap.hpp"
#include "Scene/3D/Components/Mesh.hpp"

#include <cstring>

namespace Soon
{
	class DefaultPipeline : public BasePipeline
	{
	public:
		std::vector< Transform3D* >	_transforms;
		UniformSets			_uniformCamera;
		TextureCubeMap			_skybox;

		std::vector< ImageRenderer >			_imagesRenderer;
		std::vector< std::vector< VkDescriptorSet > >	_uniformsImagesDescriptorSets;
		std::vector< Image >				_images;

		std::vector< uint32_t >				_nbVertex;
		std::vector< VkBuffer >				_gpuBuffers;
		std::vector< VkDeviceMemory >		_gpuMemoryBuffers;
		std::vector< BufferRenderer >		_stagingBuffers;
		std::vector< BufferRenderer >		_indexBuffers;
		std::vector< uint32_t >				_indexSize;

		DefaultPipeline( void )
		{
			_descriptorSetLayout = GraphicsInstance::GetInstance()->CreateDescriptorSetLayout( GetLayoutBinding() );
			_pipelineLayout = GraphicsInstance::GetInstance()->CreatePipelineLayout(_descriptorSetLayout);
			_graphicPipeline = GraphicsInstance::GetInstance()->CreateGraphicsPipeline(
					_pipelineLayout,
					GetBindingDescription(),
					GetAttributeDescriptions(),
					GraphicsInstance::ShaderType::VERTEX_FRAGMENT,
					"../Source/Graphics/Shaders/DefaultPipeline.vert.spv",
					"../Source/Graphics/Shaders/DefaultPipeline.frag.spv");

			_uniformCamera = GraphicsInstance::GetInstance()->CreateUniform(sizeof(UniformCamera), _descriptorSetLayout, 0);

			///////////////

			Mesh skybox;

			skybox.LoadMesh("../Ressources/objects/Basics/Cube.obj");

			std::vector<BufferRenderer> handler = GraphicsInstance::GetInstance()->CreateVertexBuffer(skybox._inf._vertexSize, skybox._inf._vertexData, false);

			_stagingBuffers.push_back(handler[0]);
			_gpuBuffers.push_back(handler[1]._Buffer[0]);
			_gpuMemoryBuffers.push_back(handler[1]._BufferMemory[0]);
			_indexBuffers.push_back(GraphicsInstance::GetInstance()->CreateIndexBuffer(skybox._inf));
			_nbVertex.push_back(skybox._inf._nbVertex);
			_indexSize.push_back(skybox._inf._indexSize);

			Image img;
			_imagesRenderer.push_back(GraphicsInstance::GetInstance()->CreateTextureImage(&_skybox));
			img._textureSampler = GraphicsInstance::GetInstance()->CreateTextureSampler();
			img._imageView = GraphicsInstance::GetInstance()->CreateImageView(_imagesRenderer.back()._textureImage, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_ASPECT_COLOR_BIT, VK_IMAGE_VIEW_TYPE_CUBE);
			_images.push_back(img);

			std::vector<VkDescriptorSet> imageUniform = GraphicsInstance::GetInstance()->CreateImageDescriptorSets(img._imageView, img._textureSampler, _descriptorSetLayout[1]);
			_uniformsImagesDescriptorSets.push_back(imageUniform);

			/////////////
		}

		void BindCaller( VkCommandBuffer commandBuffer, uint32_t index )
		{
			vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, _graphicPipeline);

			VkDeviceSize offsets[] = {0};

			vkCmdBindVertexBuffers(commandBuffer, 0, 1, &_gpuBuffers.at(0), offsets);
			vkCmdBindIndexBuffer(commandBuffer, _indexBuffers.at(0)._Buffer[0], 0, VK_INDEX_TYPE_UINT32);
			vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, _pipelineLayout, 0, 1, &(_uniformCamera._descriptorSets.at(index)), 0, nullptr);
			vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, _pipelineLayout, 2, 1, &_uniformsImagesDescriptorSets.at(0).at(index), 0, nullptr);

			vkCmdDrawIndexed(commandBuffer, _indexSize.at(0), 1, 0, 0, 0);
		}

		void AddToRender( void )
		{

		}

		void RecreateUniforms( void )
		{
			_uniformCamera = GraphicsInstance::GetInstance()->CreateUniform(sizeof(UniformCamera), _descriptorSetLayout, 0);
		}

		void UpdateData( int currentImage )
		{
			void* data = nullptr;
			VkDevice device = GraphicsInstance::GetInstance()->GetDevice();

			//////////// Cam ///////////
			UniformCamera uc = {};

			if (Engine::GetInstance().GetCurrentScene() && Engine::GetInstance().GetCurrentScene()->GetCurrentCamera())
			{
				uc.view = Engine::GetInstance().GetCurrentScene()->GetCurrentCamera()->GetViewMatrix();
				uc.proj = Engine::GetInstance().GetCurrentScene()->GetCurrentCamera()->GetProjectionMatrix();
			}
			else
			{
				//          std::cout << "No Current Camera.";
				uc.view = mat4<float>();
				uc.proj = mat4<float>();
			}

			std::vector<VkDeviceMemory> vkdm = _uniformCamera._uniformRender._BufferMemory;
			vkMapMemory(device, vkdm[currentImage], 0, sizeof(UniformCamera), 0, &data);
			memcpy(data, &uc, sizeof(UniformCamera));
			vkUnmapMemory(device, vkdm[currentImage]);
		}

		std::vector<VkDescriptorSetLayoutBinding> GetLayoutBinding( void )
		{
			std::vector<VkDescriptorSetLayoutBinding> uboLayoutBinding(2);

			/////// CAM /////////////
			uboLayoutBinding[0].binding = 0;
			uboLayoutBinding[0].descriptorCount = 1;
			uboLayoutBinding[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
			uboLayoutBinding[0].pImmutableSamplers = nullptr;
			uboLayoutBinding[0].stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
			//////////// IMAGE ///////////////
			uboLayoutBinding[1].binding = 0;
			uboLayoutBinding[1].descriptorCount = 1;
			uboLayoutBinding[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
			uboLayoutBinding[1].pImmutableSamplers = nullptr;
			uboLayoutBinding[1].stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;

			return (uboLayoutBinding);
		}

		VkVertexInputBindingDescription GetBindingDescription( void )
		{
			VkVertexInputBindingDescription bindingDescription = {};
			bindingDescription.binding = 0;
			bindingDescription.stride = sizeof(Vertex); // stride : size of one pointe
			bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

			return (bindingDescription);
		}

		std::vector<VkVertexInputAttributeDescription> GetAttributeDescriptions( void )
		{
			std::vector<VkVertexInputAttributeDescription> attributeDescriptions(3);

			attributeDescriptions[0].binding = 0;
			attributeDescriptions[0].location = 0;
			attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;//VK_FORMAT_R32G32_SFLOAT;
			attributeDescriptions[0].offset = offsetof(Vertex, _position);

			attributeDescriptions[1].binding = 0;
			attributeDescriptions[1].location = 1;
			attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;//VK_FORMAT_R32G32_SFLOAT;
			attributeDescriptions[1].offset = offsetof(Vertex, _normal);

			attributeDescriptions[2].binding = 0;
			attributeDescriptions[2].location = 2;
			attributeDescriptions[2].format = VK_FORMAT_R32G32B32_SFLOAT;//VK_FORMAT_R32G32_SFLOAT;
			attributeDescriptions[2].offset = offsetof(Vertex, _texCoords);

			return attributeDescriptions;
		}

		void RecreatePipeline( void )
		{

		}

		struct Properties
		{
		} _properties;
	};
}
