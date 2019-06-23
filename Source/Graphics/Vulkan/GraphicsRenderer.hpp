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
	class DirectionalLight;

	class GraphicsRenderer
	{
		static GraphicsRenderer* _instance;

		public:
		GraphicsRenderer( void );
		static GraphicsRenderer* 	GetInstance( void );
		void 				Initialize( void );
		void 				AddToRender( Transform3D& tr, VertexBufferInfo inf);
		void AddLightToRender( Transform3D& tr, DirectionalLight* dl);
//		std::vector< VkBuffer >		GetvkBuffers( void );
//		std::vector< uint32_t >		GetNbVertex( void );
		bool				HasChange( void );
		void				SetChangeFalse( void );
//		std::vector< BufferRenderer >	GetUniformBuffers( void );
//		std::vector< std::vector<VkDescriptorSet> > GetUniformsDescriptorSets( void );
//		std::vector< Transform3D* >	GetTransforms( void );
//		UniformSets			GetUniformsCamera( void );
//		std::vector<VkDescriptorSet>	GetUniformCameraDescriptorSets( void );
//		std::vector< VkDeviceMemory >   GetVkDeviceMemory( void );
		void 				RecreateAllUniforms( void );
//		std::vector< BufferRenderer >   GetIndexBuffers( void );
//		std::vector<uint32_t>   GetIndexSize( void );
//		std::vector< std::vector<VkDescriptorSet> > GetUniformsImagesDescriptorSets( void );

//		std::vector< std::vector<VkDescriptorSet> > GetUniformsMaterialsDescriptorSets( void );
//		std::vector< BufferRenderer > GetUniformsMaterials( void );
//		std::vector< Material * > GetMaterials( void );
//		std::vector< std::vector<VkDescriptorSet> > GetUniformsLightsDescriptorSets( void );
//		std::vector< BufferRenderer > GetUniformsLights( void );
//		std::vector< DirectionalLight * > GetLights( void );

		private:
		std::vector<BasePipeline*>		_pipelines;
		bool _changes;
	};
}
