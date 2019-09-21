#pragma once

#include "Graphics/Pipelines/BasePipeline.hpp"
#include "Core/Engine.hpp"
#include "Scene/3D/Components/Camera.hpp"
#include "Scene/3D/Components/DirectionalLight.hpp"

#include <cstring>


namespace Soon
{
	struct DefaultVertexPipeline : BasePipeline
	{
		DefaultVertexPipeline( void )
		{
			_descriptorSetLayout = GraphicsInstance::GetInstance()->CreateDescriptorSetLayout( GetLayoutBinding() );
			_pipelineLayout = GraphicsInstance::GetInstance()->CreatePipelineLayout(_descriptorSetLayout);
			_graphicPipeline = GraphicsInstance::GetInstance()->CreateGraphicsPipeline(
					_pipelineLayout,
					GetBindingDescription(),
					GetAttributeDescriptions(),
					GraphicsInstance::ShaderType::VERTEX_FRAGMENT,
					"../Source/Graphics/Shaders/Default_Shader.vert.spv",
					"../Source/Graphics/Shaders/Default_Shader.frag.spv");

			_uniformCamera = GraphicsInstance::GetInstance()->CreateUniform(sizeof(UniformCamera), _descriptorSetLayout, 0);
		}

		struct Properties
		{
			Texture2D _texture;
			alignas(16) vec3<float> _ambient;
			alignas(16) vec3<float> _diffuse;
			alignas(16) vec3<float> _specular;
			alignas(4)  float       _shininess;
		};

		std::vector< uint32_t >				_nbVertex;
		std::vector< Transform3D* >			_transforms;
		std::vector< VkBuffer >				_gpuBuffers;
		std::vector< VkDeviceMemory >		_gpuMemoryBuffers;
		std::vector< BufferRenderer >		_stagingBuffers;
		std::vector< BufferRenderer >		_indexBuffers;
		std::vector< uint32_t >				_indexSize;

		std::vector< ImageRenderer >		_imagesRenderer;
		std::vector< std::vector< VkDescriptorSet > >	_uniformsImagesDescriptorSets;
		std::vector< Image >			_images;

		// UNIFORM
		std::vector< BufferRenderer > 	_uniformsBuffers;
		std::vector< std::vector< VkDescriptorSet > >	_uniformsDescriptorSets;

		//// UNIFORM CAMERA
		UniformSets						_uniformCamera;

		// UNIFORM MATERIAL
		std::vector<Material*>			_vecMaterials;
		std::vector< BufferRenderer > 	_uniformsMaterials;
		std::vector< std::vector< VkDescriptorSet > >	_uniformsMaterialsDescriptorSets;

		// UNIFORM LIGHT
		std::vector<DirectionalLight*>		_vecLights;
		std::vector< BufferRenderer > 	_uniformsLights;
		std::vector< std::vector< VkDescriptorSet > >	_uniformsLightsDescriptorSets;

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

			/////////// Model //////////
			////////////// NEED TO MERGE MATERIAL AND MODEL

			data = nullptr;

			// For Every Uniform
			int i = -1;
			for (auto& uniform : _uniformsBuffers)
			{
				++i;

				vkMapMemory(device, uniform._BufferMemory[currentImage], 0, sizeof(UniformModel), 0, &data);

				mat4<float> matModel;

				Transform3D* transform = _transforms.at(i);

				matModel = transform->_rot.GetRotationMatrix();

				matModel(0,3) = transform->_pos.x;
				matModel(1,3) = transform->_pos.y;
				matModel(2,3) = transform->_pos.z;

				matModel(0,0) *= transform->_scale.x;
				matModel(1,1) *= transform->_scale.y;
				matModel(2,2) *= transform->_scale.z;

				memcpy(data, &matModel, sizeof(UniformModel));
				vkUnmapMemory(device, uniform._BufferMemory[currentImage]);
			}
			data = nullptr;

			///// MATERIALS
			i = -1;
			for (auto& uniformMaterial : _uniformsMaterials)
			{
				++i;

				DefaultVertexPipeline::Properties* mt = reinterpret_cast<DefaultVertexPipeline::Properties*>(_vecMaterials.at(i)->_properties);

				vkMapMemory(device, uniformMaterial._BufferMemory[currentImage], 0, sizeof(UniformMaterial), 0, &data);
				memcpy(data, &(mt->_ambient), sizeof(UniformMaterial));
				vkUnmapMemory(device, uniformMaterial._BufferMemory[currentImage]);
			}
			data = nullptr;

			///////// LIGHTs
			i = -1;
			for (auto& uniformLight : _uniformsLights)
			{
				++i;
				vkMapMemory(device, uniformLight._BufferMemory[currentImage], 0, sizeof(UniformLight), 0, &data);
				memcpy(data, &(_vecLights.at(i)->_direction), sizeof(UniformLight));
				vkUnmapMemory(device, uniformLight._BufferMemory[currentImage]);
			}

		}

		void BindCaller( VkCommandBuffer commandBuffer, uint32_t index )
		{
			vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, _graphicPipeline);

			VkDeviceSize offsets[] = {0};

			// Bind Cam
			if (!_gpuBuffers.empty())
				vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, _pipelineLayout, 0, 1, &(_uniformCamera._descriptorSets.at(index)), 0, nullptr);

			vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, _pipelineLayout, 4, 1, &(_uniformsLightsDescriptorSets.at(0).at(index)), 0, nullptr);

			uint32_t j = 0;
			for (auto& buf : _gpuBuffers)
			{
				vkCmdBindVertexBuffers(commandBuffer, 0, 1, &buf, offsets);

				vkCmdBindIndexBuffer(commandBuffer, _indexBuffers.at(j)._Buffer[0], 0, VK_INDEX_TYPE_UINT32);

				vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, _pipelineLayout, 1, 1, &_uniformsDescriptorSets.at(j).at(index), 0, nullptr);
				vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, _pipelineLayout, 2, 1, &_uniformsImagesDescriptorSets.at(j).at(index), 0, nullptr);

				vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, _pipelineLayout, 3, 1, &_uniformsMaterialsDescriptorSets.at(j).at(index), 0  , nullptr);

				vkCmdDrawIndexed(commandBuffer, _indexSize.at(j), 1, 0, 0, 0);
				++j;
			}
		}

		std::vector<VkDescriptorSetLayoutBinding> GetLayoutBinding( void )
		{
			std::vector<VkDescriptorSetLayoutBinding> uboLayoutBinding(5);

			////// BINDING 0 : CAM //////////
			uboLayoutBinding[0].binding = 0;
			uboLayoutBinding[0].descriptorCount = 1;
			uboLayoutBinding[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
			uboLayoutBinding[0].pImmutableSamplers = nullptr;
			uboLayoutBinding[0].stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
			////// BINDING 1 : MODEL //////////
			uboLayoutBinding[1].binding = 0;
			uboLayoutBinding[1].descriptorCount = 1;
			uboLayoutBinding[1].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
			uboLayoutBinding[1].pImmutableSamplers = nullptr;
			uboLayoutBinding[1].stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
			//////////// IMAGE ///////////////
			uboLayoutBinding[2].binding = 0;
			uboLayoutBinding[2].descriptorCount = 1;
			uboLayoutBinding[2].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
			uboLayoutBinding[2].pImmutableSamplers = nullptr;
			uboLayoutBinding[2].stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
			///////// MATERIALS /////////////
			uboLayoutBinding[3].binding = 0;
			uboLayoutBinding[3].descriptorCount = 1;
			uboLayoutBinding[3].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
			uboLayoutBinding[3].pImmutableSamplers = nullptr;
			uboLayoutBinding[3].stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
			///////////// LIGHTS ////////////
			uboLayoutBinding[4].binding = 0;
			uboLayoutBinding[4].descriptorCount = 1;
			uboLayoutBinding[4].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
			uboLayoutBinding[4].pImmutableSamplers = nullptr;
			uboLayoutBinding[4].stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;

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

		void AddToRender( Transform3D& tr, VertexBufferInfo inf )
		{
			std::vector<BufferRenderer> handler = GraphicsInstance::GetInstance()->CreateVertexBuffer(inf._vertexSize, inf._vertexData, false);
			//      ComponentRenderer ret;

			_stagingBuffers.push_back(handler[0]);
			_gpuBuffers.push_back(handler[1]._Buffer[0]);
			_gpuMemoryBuffers.push_back(handler[1]._BufferMemory[0]);

			_indexBuffers.push_back(GraphicsInstance::GetInstance()->CreateIndexBuffer(inf));

			_nbVertex.push_back(inf._nbVertex);
			_indexSize.push_back(inf._indexSize);
			_transforms.push_back(&tr);

			//			ret._transform = _transforms.end();
			//			ret._vkBuffers = _gpuBuffers.end();
			//			ret._vkDevicesMemoryBuffers = _gpuMemoryBuffers.end();

			///////////// UNIFORM /////////////

			UniformSets modelUniform = GraphicsInstance::GetInstance()->CreateUniform(sizeof(UniformModel), _descriptorSetLayout, 1);

			_uniformsBuffers.push_back(modelUniform._uniformRender);
			_uniformsDescriptorSets.push_back(modelUniform._descriptorSets);

			///////////// TEXTURE ////////////

			Image img;
			DefaultVertexPipeline::Properties* prop = reinterpret_cast<DefaultVertexPipeline::Properties*>(inf._material->_properties);

			std::cout << prop->_texture._width << " " << prop->_texture._height << std::endl;
			_imagesRenderer.push_back(GraphicsInstance::GetInstance()->CreateTextureImage(&(prop->_texture)));
			img._textureSampler = GraphicsInstance::GetInstance()->CreateTextureSampler();
			img._imageView = GraphicsInstance::GetInstance()->CreateImageView(_imagesRenderer.back()._textureImage, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_ASPECT_COLOR_BIT);
			_images.push_back(img);

			std::vector<VkDescriptorSet> imageUniform = GraphicsInstance::GetInstance()->CreateImageDescriptorSets(img._imageView, img._textureSampler, _descriptorSetLayout[2]);
			_uniformsImagesDescriptorSets.push_back(imageUniform);

			/////////// MATERIAL //////////////

			UniformSets matUniform = GraphicsInstance::GetInstance()->CreateUniform(sizeof(UniformMaterial), _descriptorSetLayout, 3);

			_uniformsMaterials.push_back(matUniform._uniformRender);
			_uniformsMaterialsDescriptorSets.push_back(matUniform._descriptorSets);
			_vecMaterials.push_back(inf._material);

			/////////////////

			//			return ret;
		}

		void RecreateUniforms( void )
		{
			_uniformCamera = GraphicsInstance::GetInstance()->CreateUniform(sizeof(UniformCamera), _descriptorSetLayout, 0);

			std::size_t j = 0;
			while (j < _uniformsBuffers.size())
			{
				UniformSets modelUniform = GraphicsInstance::GetInstance()->CreateUniform(sizeof(UniformModel), _descriptorSetLayout, 1);
				_uniformsBuffers.at(j) = modelUniform._uniformRender;
				_uniformsDescriptorSets.at(j) = modelUniform._descriptorSets;
				++j;
			}
			j = 0;
			while (j < _uniformsImagesDescriptorSets.size())
			{
				std::vector<VkDescriptorSet> imageUniform = GraphicsInstance::GetInstance()->CreateImageDescriptorSets(_images.at(j)._imageView, _images.at(j)._textureSampler, _descriptorSetLayout[2]);
				_uniformsImagesDescriptorSets.at(j) = imageUniform;
				++j;
			}

			/// RECREATE MATERIALS
			j = 0;
			while (j < _uniformsMaterialsDescriptorSets.size())
			{
				UniformSets matUniform = GraphicsInstance::GetInstance()->CreateUniform(sizeof(UniformMaterial), _descriptorSetLayout, 3);
				_uniformsMaterials.at(j) = matUniform._uniformRender;
				_uniformsMaterialsDescriptorSets.at(j) = matUniform._descriptorSets;
				++j;
			}

			///// RECREATE LIGHTS
			j = 0;
			while (j < _vecLights.size())
			{
				UniformSets lightUniform = GraphicsInstance::GetInstance()->CreateUniform(sizeof(UniformLight), _descriptorSetLayout, 4);
				_uniformsLights.at(j) = lightUniform._uniformRender;
				_uniformsLightsDescriptorSets.at(j) = lightUniform._descriptorSets;
				++j;
			}
		}
		
		void AddLightToRender( Transform3D& tr, DirectionalLight* dl)
		{
			UniformSets lightUniform = GraphicsInstance::GetInstance()->CreateUniform(sizeof(UniformLight), _descriptorSetLayout, 4);

			_uniformsLights.push_back(lightUniform._uniformRender);
			_uniformsLightsDescriptorSets.push_back(lightUniform._descriptorSets);

			_vecLights.push_back(dl);
		}

		void RecreatePipeline( void )
		{
			_graphicPipeline = GraphicsInstance::GetInstance()->CreateGraphicsPipeline(
					_pipelineLayout,
					GetBindingDescription(),
					GetAttributeDescriptions(),
					GraphicsInstance::ShaderType::VERTEX_FRAGMENT,
					"../Source/Graphics/Shaders/Default_Shader.vert.spv",
					"../Source/Graphics/Shaders/Default_Shader.frag.spv");
		}
	};
}
