#include "Graphics/Pipelines/BasePipeline.hpp"
#include "Core/Engine.hpp"
#include "Scene/3D/Components/Camera.hpp"
#include "Scene/3D/Components/ParticlesSystem.hpp"

#include <cstring>

namespace Soon
{
	struct DefaultParticlesSystemPipeline : BasePipeline
	{
		public:
			struct Particle
			{
				vec3<float> _position;
				vec3<float> _velocity;
			};

			VkPipeline _computePipeline;
			VkPipelineLayout _computePipelineLayout;
			std::vector<VkDescriptorSetLayout>	_computeDescriptorSetLayout;

			std::vector< Transform3D* >			_transforms;
			std::vector< VkBuffer >				_gpuBuffers;
			std::vector< VkDeviceMemory >		_gpuMemoryBuffers;
			std::vector< BufferRenderer >		_stagingBuffers;
			std::vector< uint32_t >			_pSize;

			//// UNIFORM CAMERA
			UniformSets						_uniformCamera;

			std::vector< std::vector< VkDescriptorSet > >		_particlesDescriptorSets;

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
						_computePipelineLayout,
						"../Source/Graphics/Shaders/DefaultParticles.comp.spv");
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
				uint32_t j = 0;
				// Compute //
				vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE, _computePipeline);
				for (auto& buf : _gpuBuffers)
				{
					vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE, _computePipelineLayout, 0, 1, &(_particlesDescriptorSets.at(j).at(index)), 0, nullptr);
					vkCmdDispatch(commandBuffer, _pSize.at(j), 1, 1);
					j++;
				}
				// Graphic //
				vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, _graphicPipeline);
					// Bind Cam
				vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, _pipelineLayout, 0, 1, &(_uniformCamera._descriptorSets.at(index)), 0, nullptr);

				VkDeviceSize offsets[] = {0};

				j = 0;
				for (auto& buf : _gpuBuffers)
				{
					vkCmdBindVertexBuffers(commandBuffer, 0, 1, &buf, offsets);

					vkCmdDraw(commandBuffer, _pSize.at(j), 1, 0, 0);
					j++;
				}
			}

			std::vector<VkDescriptorSetLayoutBinding> GetLayoutBinding( void )
			{
				std::vector<VkDescriptorSetLayoutBinding> uboLayoutBinding(2);

				////// BINDING 0 : CAM //////////
				uboLayoutBinding[0].binding = 0;
				uboLayoutBinding[0].descriptorCount = 1;
				uboLayoutBinding[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
				uboLayoutBinding[0].pImmutableSamplers = nullptr;
				uboLayoutBinding[0].stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
				////// BINDING 0 : Particles //////////
				uboLayoutBinding[1].binding = 0;
				uboLayoutBinding[1].descriptorCount = 1;
				uboLayoutBinding[1].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
				uboLayoutBinding[1].pImmutableSamplers = nullptr;
				uboLayoutBinding[1].stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

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
				std::vector<BufferRenderer>                                     bufRenderer;
				VkDevice device = GraphicsInstance::GetInstance()->GetDevice();


				bufRenderer = GraphicsInstance::GetInstance()->CreateVertexBuffer(ps->_size * sizeof(Particle), nullptr, true);

				_pSize.push_back(ps->_size);
				_transforms.push_back(&tr);
				_gpuBuffers.push_back(bufRenderer[1]._Buffer[0]);
				_gpuMemoryBuffers.push_back(bufRenderer[1]._BufferMemory[0]);
				_stagingBuffers.push_back(bufRenderer[0]);

				std::cout << "Create Particle System Descriptor Set" << std::endl;
				_particlesDescriptorSets.push_back(GraphicsInstance::GetInstance()->CreateDescriptorSets(ps->_size * sizeof(Particle), _computeDescriptorSetLayout, 0, bufRenderer[1]._Buffer[0], VK_DESCRIPTOR_TYPE_STORAGE_BUFFER));
				std::cout << "END : Create Particle System Descriptor Set" << std::endl;
			}

			void RecreateUniforms( void )
			{
				uint32_t j = 0;
				_uniformCamera = GraphicsInstance::GetInstance()->CreateUniform(sizeof(UniformCamera), _descriptorSetLayout, 0);
				for (auto& pDs : _particlesDescriptorSets)
				{
					pDs = GraphicsInstance::GetInstance()->CreateDescriptorSets(_pSize.at(j) * sizeof(Particle), _computeDescriptorSetLayout, 0, _gpuBuffers.at(j), VK_DESCRIPTOR_TYPE_STORAGE_BUFFER);
					++j;
				}
			}
	};
}
