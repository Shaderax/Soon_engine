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
		UniformSets						_uniformCamera;

//		// TEXTURE
//		std::vector< BufferRenderer > 	_textureBuffers;

		bool _changes;

	};
}
