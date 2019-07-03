#include "Graphics/Pipelines/BasePipeline.hpp"
#include "Core/Engine.hpp"
#include "Scene/3D/Components/Camera.hpp"

#include <cstring>

namespace Soon
{
	struct DefaultParticlesSystemPipeline : BasePipeline
	{
		public:
			struct Particle
			{
				vec3<float> position;
				vec3<float> velocity;
			};

			VkPipeline _computePipeline;
			VkPipelineLayout _computePipelineLayout;
			VkDescriptorSetLayout _computeDescriptorSetLayout;

		DefaultParticlesSystemPipeline( void )
		{
			_descriptorSetLayout = GraphicsInstance::GetInstance()->CreateDescriptorSetLayout( GetLayoutBinding() );
			_pipelineLayout = GraphicsInstance::GetInstance()->CreatePipelineLayout(_descriptorSetLayout);
			_graphicPipeline = GraphicsInstance::GetInstance()->CreateGraphicsPipeline(
					_pipelineLayout,
					GetBindingDescription(),
					GetAttributeDescriptions(),
					GraphicsInstance::ShaderType::COMPUTE,
					"../Source/Graphics/Shaders/DefaultParticles.vert.spv",
					"../Source/Graphics/Shaders/DefaultParticles.frag.spv");

			_computeDescriptorSetLayout = GraphicsInstance::GetInstance()->CreateDescriptorSetLayout( GetComputeLayoutBinding() );
			_computePipelineLayout = GraphicsInstance::GetInstance()->CreatePipelineLayout(_computeDescriptorSetLayout);
			_computePipeline = GraphicsInstance::GetInstance()->CreateComputePipeline(
					_pipelineLayout,
					"../Source/Graphics/Shaders/DefaultParticles.comp.spv",

			_uniformCamera = GraphicsInstance::GetInstance()->CreateUniform(sizeof(UniformCamera), _descriptorSetLayout, 0);
		}

		struct Properties
		{
//			Texture2D _texture;
//			alignas(16) vec3<float> _ambient;
//			alignas(16) vec3<float> _diffuse;
//			alignas(16) vec3<float> _specular;
//			alignas(4)  float       _shininess;
		};

//		std::vector< uint32_t >				_nbVertex;
		std::vector< Transform3D* >			_transforms;
		std::vector< VkBuffer >				_gpuBuffers;
		std::vector< VkDeviceMemory >		_gpuMemoryBuffers;
		std::vector< BufferRenderer >		_stagingBuffers;
//		std::vector< BufferRenderer >		_indexBuffers;
//		std::vector< uint32_t >				_indexSize;

		// UNIFORM
//		std::vector< BufferRenderer > 	_uniformsBuffers;
//		std::vector< std::vector< VkDescriptorSet > >	_uniformsDescriptorSets;

		//// UNIFORM CAMERA
		UniformSets						_uniformCamera;

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
//			vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, _graphicPipeline);

//			VkDeviceSize offsets[] = {0};

			// Bind Cam
//			if (!_gpuBuffers.empty())
//				vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, _pipelineLayout, 0, 1, &(_uniformCamera._descriptorSets.at(index)), 0, nullptr);

//			vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, _pipelineLayout, 4, 1, &(_uniformsLightsDescriptorSets.at(0).at(index)), 0, nullptr);

//			uint32_t j = 0;
//			for (auto& buf : _gpuBuffers)
//			{
//				vkCmdBindVertexBuffers(commandBuffer, 0, 1, &buf, offsets);

//				vkCmdBindIndexBuffer(commandBuffer, _indexBuffers.at(j)._Buffer[0], 0, VK_INDEX_TYPE_UINT32);

//				vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, _pipelineLayout, 1, 1, &_uniformsDescriptorSets.at(j).at(index), 0, nullptr);
//				vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, _pipelineLayout, 2, 1, &_uniformsImagesDescriptorSets.at(j).at(index), 0, nullptr);

//				vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, _pipelineLayout, 3, 1, &_uniformsMaterialsDescriptorSets.at(j).at(index), 0  , nullptr);

//				vkCmdDrawIndexed(commandBuffer, _indexSize.at(j), 1, 0, 0, 0);
//				j++;
//			}
		}

		std::vector<VkDescriptorSetLayoutBinding> GetLayoutBinding( void )
		{
			std::vector<VkDescriptorSetLayoutBinding> uboLayoutBinding(1);

			////// BINDING 0 : CAM //////////
			uboLayoutBinding[0].binding = 0;
			uboLayoutBinding[0].descriptorCount = 1;
			uboLayoutBinding[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
			uboLayoutBinding[0].pImmutableSamplers = nullptr;
			uboLayoutBinding[0].stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

			return (uboLayoutBinding);
		}

		std::vector<VkDescriptorSetLayoutBinding> GetComputeLayoutBinding( void )
		{
			std::vector<VkDescriptorSetLayoutBinding> uboLayoutBinding(1);

			///////////// PARTICLES ////////////
			uboLayoutBinding[0].binding = 0;
			uboLayoutBinding[0].descriptorCount = 1;
			uboLayoutBinding[0].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
			uboLayoutBinding[0].pImmutableSamplers = nullptr;
			uboLayoutBinding[0].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;

			return (uboLayoutBinding);
		}

		VkVertexInputBindingDescription GetBindingDescription( void )
		{
			VkVertexInputBindingDescription bindingDescription = {};
			bindingDescription.binding = 0;
			bindingDescription.stride = sizeof(Particle);//sizeof(Vertex); // stride : size of one pointe
			bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

			return (bindingDescription);
		}

		std::vector<VkVertexInputAttributeDescription> GetAttributeDescriptions( void )
		{
			std::vector<VkVertexInputAttributeDescription> attributeDescriptions(1);

			attributeDescriptions[0].binding = 0;
			attributeDescriptions[0].location = 0;
			attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;//VK_FORMAT_R32G32_SFLOAT;
			attributeDescriptions[0].offset = offsetof(Particle, _position);

			return attributeDescriptions;
		}

		void AddToRender( Transform3D& tr, ParticlesSystem* ps )
		{
//			std::vector<BufferRenderer> handler = GraphicsInstance::GetInstance()->CreateVertexBuffer(inf);

//			_stagingBuffers.push_back(handler[0]);
//			_gpuBuffers.push_back(handler[1]._Buffer[0]);
//			_gpuMemoryBuffers.push_back(handler[1]._BufferMemory[0]);

//			_indexBuffers.push_back(GraphicsInstance::GetInstance()->CreateIndexBuffer(inf));

//			_nbVertex.push_back(inf._nbVertex);
//			_indexSize.push_back(inf._indexSize);
//			_transforms.push_back(&tr);

			///////////// UNIFORM /////////////

//			UniformSets modelUniform = GraphicsInstance::GetInstance()->CreateUniform(sizeof(UniformModel), _descriptorSetLayout, 1);

//			_uniformsBuffers.push_back(modelUniform._uniformRender);
//			_uniformsDescriptorSets.push_back(modelUniform._descriptorSets);

		}

		void RecreateUniforms( void )
		{
//			_uniformCamera = GraphicsInstance::GetInstance()->CreateUniform(sizeof(UniformCamera), _descriptorSetLayout, 0);

//			int j = -1;
//			while (++j < _uniformsBuffers.size())
//			{
//				UniformSets modelUniform = GraphicsInstance::GetInstance()->CreateUniform(sizeof(UniformModel), _descriptorSetLayout, 1);
//				_uniformsBuffers.at(j) = modelUniform._uniformRender;
//				_uniformsDescriptorSets.at(j) = modelUniform._descriptorSets;
//			}
//
		}
	};
}
