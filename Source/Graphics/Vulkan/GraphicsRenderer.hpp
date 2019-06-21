#pragma once

#include "Graphics/Vulkan/GraphicsInstance.hpp"
#include "Scene/3D/Components/Transform3D.hpp"
#include "Core/Math/mat4.hpp"

struct Image
{
	VkSampler _textureSampler;
	VkImageView _imageView;
};

namespace Soon
{
	class BasePipeline
	{
		virtual void GetLayoutBinding( void );
		virtual void GetBindingDescription( void );
		virtual UpdateData( int currentImg );
		virtual void BindCaller( VkCommandBuffer commandBuffer );
		virtual void GetAttributeDescriptions( void );
	};

	class DefaultVertexPipeline : BasePipeline
	{
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

		void UpdateData( int currentImg )
		{
			void* data = nullptr;

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

			std::vector<VkDeviceMemory> vkdm = GraphicsRenderer::GetInstance()->GetUniformsCamera()._uniformRender._BufferMemory;
			vkMapMemory(_device, vkdm[currentImage], 0, sizeof(UniformCamera), 0, &data);
			memcpy(data, &uc, sizeof(UniformCamera));
			vkUnmapMemory(_device, vkdm[currentImage]);

			/////////// Model //////////
			////////////// NEED TO MERGE MATERIAL AND MODEL

			data = nullptr;

			// For Every Uniform
			int i = -1;
			for (auto& uniform : GraphicsRenderer::GetInstance()->GetUniformBuffers())
			{
				++i;

				vkMapMemory(_device, uniform._BufferMemory[currentImage], 0, sizeof(UniformModel), 0, &data);

				mat4<float> matModel;

				Transform3D* transform = GraphicsRenderer::GetInstance()->GetTransforms().at(i);

				matModel = transform->_rot.GetRotationMatrix();

				matModel(0,3) = transform->_pos.x;
				matModel(1,3) = transform->_pos.y;
				matModel(2,3) = transform->_pos.z;

				matModel(0,0) *= transform->_scale.x;
				matModel(1,1) *= transform->_scale.y;
				matModel(2,2) *= transform->_scale.z;

				memcpy(data, &matModel, sizeof(UniformModel));
				vkUnmapMemory(_device, uniform._BufferMemory[currentImage]);
			}
			data = nullptr;

			///// MATERIALS
			i = -1;
			for (auto& uniformMaterial : GraphicsRenderer::GetInstance()->GetUniformsMaterials())
			{
				++i;

				Material* mt = GraphicsRenderer::GetInstance()->GetMaterials().at(i);

				vkMapMemory(_device, uniformMaterial._BufferMemory[currentImage], 0, sizeof(UniformMaterial), 0, &data);
				memcpy(data, &(mt->_ambient), sizeof(UniformMaterial));
				vkUnmapMemory(_device, uniformMaterial._BufferMemory[currentImage]);
			}
			data = nullptr;

			///////// LIGHTs
			i = -1;
			for (auto& uniformLight : GraphicsRenderer::GetInstance()->GetUniformsLights())
			{
				++i;
				vkMapMemory(_device, uniformLight._BufferMemory[currentImage], 0, sizeof(UniformLight), 0, &data);
				memcpy(data, &(GraphicsRenderer::GetInstance()->GetLights().at(i)->_direction), sizeof(UniformLight));
				vkUnmapMemory(_device, uniformLight._BufferMemory[currentImage]);
			}

		}

		void BindCaller( void )
		{
			std::vector<VkBuffer> vecBuf =          GraphicsRenderer::GetInstance()->GetvkBuffers();
			std::vector< uint32_t > vecNbVer =      GraphicsRenderer::GetInstance()->GetNbVertex();
			std::vector<std::vector< VkDescriptorSet >> vecDs =         GraphicsRenderer::GetInstance()->GetUniformsDescriptorSets();
			std::vector<std::vector< VkDescriptorSet >> uniformImage =  GraphicsRenderer::GetInstance()->GetUniformsImagesDescriptorSets();
			// MATERIALS
			std::vector<std::vector< VkDescriptorSet >> uniformMaterials =  GraphicsRenderer::GetInstance()->GetUniformsMaterialsDescriptorSets();
			// LIGHTS
			std::vector<std::vector< VkDescriptorSet >> uniformLights = GraphicsRenderer::GetInstance()->GetUniformsLightsDescriptorSets();

			vkCmdBindPipeline(_commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, _graphicsPipeline);

			VkDeviceSize offsets[] = {0};

			// Bind Cam
			if (!GraphicsRenderer::GetInstance()->GetvkBuffers().empty())
				vkCmdBindDescriptorSets(_commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, _pipelineLayout, 0, 1, &(GraphicsRenderer::GetInstance(  )->GetUniformCameraDescriptorSets().at(i)), 0, nullptr);

			vkCmdBindDescriptorSets(_commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, _pipelineLayout, 4, 1, &(uniformLights.at(0).at(i)), 0, nul  lptr);

			uint32_t j = 0;
			for (auto& buf : GraphicsRenderer::GetInstance()->GetvkBuffers())
			{
				//              std::cout << "VkBuffer : " << buf << std::endl << "NbVer : " << vecNbVer.at(j) << std::endl;
				vkCmdBindVertexBuffers(_commandBuffers[i], 0, 1, &buf, offsets);

				vkCmdBindIndexBuffer(_commandBuffers[i], GraphicsRenderer::GetInstance()->GetIndexBuffers().at(j)._Buffer[0], 0, VK_INDEX_TYPE_UINT3  2);

				vkCmdBindDescriptorSets(_commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, _pipelineLayout, 1, 1, &vecDs.at(j).at(i), 0, nullptr);
				vkCmdBindDescriptorSets(_commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, _pipelineLayout, 2, 1, &uniformImage.at(j).at(i), 0, nu  llptr);

				vkCmdBindDescriptorSets(_commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, _pipelineLayout, 3, 1, &uniformMaterials.at(j).at(i), 0  , nullptr);

				//              vkCmdDraw(_commandBuffers[i], vecNbVer.at(j), 1, 0, 0);
				vkCmdDrawIndexed(_commandBuffers[i], static_cast<uint32_t>(GraphicsRenderer::GetInstance()->GetIndexSize().at(j)), 1, 0, 0, 0);
				j++;
			}
		}

		std::array<VkDescriptorSetLayoutBinding> GetLayoutBinding( void )
		{
			std::array<VkDescriptorSetLayoutBinding, 5> uboLayoutBinding;

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

		GetAttributeDescriptions( void )
		{
			std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions;

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
			attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;//VK_FORMAT_R32G32_SFLOAT;
			attributeDescriptions[2].offset = offsetof(Vertex, _texCoords);
		}
	};

	class DefaultParticlesSystemPipeline : BasePipeline
	{
		std::vector< Transform3D* >		_transforms;
		std::vector< VkBuffer >			_gpuBuffers;
		std::vector< VkDeviceMemory >	_gpuMemoryBuffers;
		UpdateData( int currentImg );
	};
	std::vector<BasePipeline*> _pipelineVector;

	class DirectionalLight;

	struct ComponentRenderer
	{
		std::vector< Transform3D* >::iterator	_transform;
		std::vector< VkBuffer >::iterator		_vkBuffers;
		std::vector< VkDeviceMemory >::iterator	_vkDevicesMemoryBuffers;
	};

	class GraphicsRenderer
	{
		static GraphicsRenderer* _instance;

		public:
		GraphicsRenderer( void );
		static GraphicsRenderer* 	GetInstance( void );
		void 				Initialize( void );
		ComponentRenderer 		AddToRender( Transform3D& tr, VertexBufferInfo inf);
		std::vector< VkBuffer >		GetvkBuffers( void );
		std::vector< uint32_t >		GetNbVertex( void );
		bool				HasChange( void );
		void				SetChangeFalse( void );
		std::vector< BufferRenderer >	GetUniformBuffers( void );
		std::vector< std::vector<VkDescriptorSet> > GetUniformsDescriptorSets( void );
		std::vector< Transform3D* >	GetTransforms( void );
		UniformSets			GetUniformsCamera( void );
		std::vector<VkDescriptorSet>	GetUniformCameraDescriptorSets( void );
		std::vector< VkDeviceMemory >   GetVkDeviceMemory( void );
		void 				RecreateAllUniforms( void );
		std::vector< BufferRenderer >   GetIndexBuffers( void );
		std::vector<uint32_t>   GetIndexSize( void );
		std::vector< std::vector<VkDescriptorSet> > GetUniformsImagesDescriptorSets( void );

		std::vector< std::vector<VkDescriptorSet> > GetUniformsMaterialsDescriptorSets( void );
		std::vector< BufferRenderer > GetUniformsMaterials( void );
		std::vector< Material * > GetMaterials( void );
		std::vector< std::vector<VkDescriptorSet> > GetUniformsLightsDescriptorSets( void );
		std::vector< BufferRenderer > GetUniformsLights( void );
		std::vector< DirectionalLight * > GetLights( void );

		void AddLightToRender( Transform3D& tr, DirectionalLight* dl);

		private:
		std::vector< uint32_t >			_nbVertex;
		std::vector< Transform3D* >		_transforms;
		std::vector< VkBuffer >			_gpuBuffers;
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

		bool _changes;
	};
}
