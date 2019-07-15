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

			//	Mesh skybox;

			//	skybox.LoadMesh();

			//	std::vector<BufferRenderer> handler = GraphicsInstance::GetInstance()->CreateVertexBuffer(inf._vertexSize, inf._vertexData, false);










				/////////////

				Image img;
				_imagesRenderer.push_back(GraphicsInstance::GetInstance()->CreateTextureImage(&_skybox));
				img._textureSampler = GraphicsInstance::GetInstance()->CreateTextureSampler();
				img._imageView = GraphicsInstance::GetInstance()->CreateImageView(_imagesRenderer.back()._textureImage, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_ASPECT_COLOR_BIT, VK_IMAGE_VIEW_TYPE_CUBE);
				_images.push_back(img);

				std::vector<VkDescriptorSet> imageUniform = GraphicsInstance::GetInstance()->CreateImageDescriptorSets(img._imageView, img._textureSampler, _descriptorSetLayout[1]);
				_uniformsImagesDescriptorSets.push_back(imageUniform);
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

			void BindCaller( VkCommandBuffer commandBuffer, uint32_t index )
			{
				vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, _graphicPipeline);

				vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, _pipelineLayout, 0, 1, &(_uniformCamera._descriptorSets.at(index)), 0, nullptr);
			}

			std::vector<VkDescriptorSetLayoutBinding> GetLayoutBinding( void )
			{
				std::vector<VkDescriptorSetLayoutBinding> uboLayoutBinding(2);

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
				bindingDescription.stride = sizeof(vec3<float>);//sizeof(Vertex); // stride : size of one pointe
				bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

				return (bindingDescription);
			}

			std::vector<VkVertexInputAttributeDescription> GetAttributeDescriptions( void )
			{
				std::vector<VkVertexInputAttributeDescription> attributeDescriptions(1);

				attributeDescriptions[0].binding = 0;
				attributeDescriptions[0].location = 0;
				attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;//VK_FORMAT_R32G32_SFLOAT;
				attributeDescriptions[0].offset = 0;

				return (attributeDescriptions);
			}

			void RecreatePipeline( void )
			{

			}

			struct Properties
			{
			} _properties;
	};
}
