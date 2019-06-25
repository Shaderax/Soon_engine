#pragma once

#include "Graphics/Vulkan/GraphicsInstance.hpp"
#include "Scene/3D/Components/Transform3D.hpp"
#include "Core/Math/mat4.hpp"

#include <bitset>
#include <array>

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
		static constexpr const std::uint32_t MAX_PIPELINES = 64;
		static GraphicsRenderer* _instance;

		public:
		GraphicsRenderer( void );
		static GraphicsRenderer* 	GetInstance( void );
		void 				Initialize( void );
		void 				AddVertexToRender( Transform3D& tr, VertexBufferInfo inf);
		void AddLightToRender( Transform3D& tr, DirectionalLight* dl);
		bool				HasChange( void );
		void				SetChangeFalse( void );
		void 				RecreateAllUniforms( void );
		void 				PipelinesBindCaller( VkCommandBuffer commandBuffer, uint32_t index );
		void				UpdateAllDatas( uint32_t imageIndex );

		template<typename T>
		void AddPipeline( void );

//		std::vector< VkBuffer >		GetvkBuffers( void );
//		std::vector< uint32_t >		GetNbVertex( void );
//		std::vector< BufferRenderer >	GetUniformBuffers( void );
//		std::vector< std::vector<VkDescriptorSet> > GetUniformsDescriptorSets( void );
//		std::vector< Transform3D* >	GetTransforms( void );
//		UniformSets			GetUniformsCamera( void );
//		std::vector<VkDescriptorSet>	GetUniformCameraDescriptorSets( void );
//		std::vector< VkDeviceMemory >   GetVkDeviceMemory( void );
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
		std::array<BasePipeline*, MAX_PIPELINES>		_pipelines;
		bool _changes;
		bool _isDefault;
		std::bitset<MAX_PIPELINES>					_createdPipeline;

		
	};
}
