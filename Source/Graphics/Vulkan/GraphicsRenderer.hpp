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
//	class BasePipeline
//	{
//		virtual UpdateData( int currentImg);
//	};
//
//	class DefaultVertexPipeline : BasePipeline
//	{
//		std::vector< uint32_t >			_nbVertex;
//		std::vector< Transform3D* >		_transforms;
//		std::vector< VkBuffer >			_gpuBuffers;
//		std::vector< VkDeviceMemory >		_gpuMemoryBuffers;
//		std::vector< BufferRenderer >		_stagingBuffers;
//		std::vector< BufferRenderer >		_indexBuffers;
//		std::vector< uint32_t >				_indexSize;
//
//		std::vector< ImageRenderer >		_imagesRenderer;
//		std::vector< std::vector< VkDescriptorSet > >	_uniformsImagesDescriptorSets;
//		std::vector< Image >			_images;
//
//		// UNIFORM
//		std::vector< BufferRenderer > 	_uniformsBuffers;
//		std::vector< std::vector< VkDescriptorSet > >	_uniformsDescriptorSets;
//
//		//// UNIFORM CAMERA
//		UniformSets						_uniformCamera;
//
//		// UNIFORM MATERIAL
//		std::vector<Material*>			_vecMaterials;
//		std::vector< BufferRenderer > 	_uniformsMaterials;
//		std::vector< std::vector< VkDescriptorSet > >	_uniformsMaterialsDescriptorSets;
//
//		// UNIFORM LIGHT
//		std::vector<DirectionalLight*>		_vecLights;
//		std::vector< BufferRenderer > 	_uniformsLights;
//		std::vector< std::vector< VkDescriptorSet > >	_uniformsLightsDescriptorSets;
//
//		UpdateData( int currentImg );
//	};
//
//	class DefaultParticlesSystemPipeline : BasePipeline
//	{
//		std::vector< Transform3D* >		_transforms;
//		std::vector< VkBuffer >			_gpuBuffers;
//		std::vector< VkDeviceMemory >	_gpuMemoryBuffers;
//		UpdateData( int currentImg );
//	};
//	std::vector<BasePipeline*> _pipelineVector;

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
