#include "Graphics/Pipelines/BasePipeline.hpp"
#include "Graphics/Vulkan/GraphicsInstance.hpp"
#include "Core/Engine.hpp"
#include "Scene/3D/Components/Camera.hpp"

#include <cstring>

namespace Soon
{
	class DefaultPipeline : public BasePipeline
	{
		public:
		std::vector< Transform3D* >	_transforms;
		UniformSets			_uniformCamera;

		DefaultPipeline( void )
		{
			_descriptorSetLayout = GraphicsInstance::GetInstance()->CreateDescriptorSetLayout( GetLayoutBinding() );
			_pipelineLayout = GraphicsInstance::GetInstance()->CreatePipelineLayout(_descriptorSetLayout);
			_graphicPipeline = GraphicsInstance::GetInstance()->CreateGraphicsPipeline(
					_pipelineLayout,
					GetBindingDescription(),
					GetAttributeDescriptions(),
					"../Source/Graphics/Shaders/DefaultPipeline.vert.spv",
					"../Source/Graphics/Shaders/DefaultPipeline.frag.spv");

			_uniformCamera = GraphicsInstance::GetInstance()->CreateUniform(sizeof(UniformCamera), _descriptorSetLayout, 0);
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
			std::vector<VkDescriptorSetLayoutBinding> uboLayoutBinding(1);

			uboLayoutBinding[0].binding = 0;
			uboLayoutBinding[0].descriptorCount = 1;
			uboLayoutBinding[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
			uboLayoutBinding[0].pImmutableSamplers = nullptr;
			uboLayoutBinding[0].stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

			return (uboLayoutBinding);
		}

		VkVertexInputBindingDescription GetBindingDescription( void )
		{
			VkVertexInputBindingDescription bindingDescription = {};
			bindingDescription.binding = 0;
			bindingDescription.stride = 0;//sizeof(Vertex); // stride : size of one pointe
			bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

			return (bindingDescription);
		}

		std::vector<VkVertexInputAttributeDescription> GetAttributeDescriptions( void )
		{
			std::vector<VkVertexInputAttributeDescription> attributeDescriptions;

			return (attributeDescriptions);
		}

		struct Properties
		{
		} _properties;
	};
}
