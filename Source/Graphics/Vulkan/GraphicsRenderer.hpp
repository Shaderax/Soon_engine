#pragma once

#include "Graphics/Vulkan/GraphicsInstance.hpp"
#include "Scene/3D/Components/Transform3D.hpp"
#include "Core/Math/mat4.hpp"

#include <bitset>
#include <array>

namespace Soon
{
	class DirectionalLight;
	class ParticlesSystem;

	class GraphicsRenderer
	{
		static constexpr const std::uint32_t MAX_PIPELINES = 32;
		static GraphicsRenderer* _instance;

		public:
		GraphicsRenderer( void );
		static GraphicsRenderer* 	GetInstance( void );
		void 				Initialize( void );
		bool				HasChange( void );
		void				SetChangeFalse( void );
		void 				RecreateAllUniforms( void );
		void 				RecreateAllPipelines( void );
		void 				GraphicPipelinesBindCaller( VkCommandBuffer commandBuffer, uint32_t index );
		void 				ComputePipelinesBindCaller( VkCommandBuffer commandBuffer, uint32_t index );
		void				UpdateAllDatas( uint32_t imageIndex );

		void 				AddVertexToRender( Transform3D& tr, VertexBufferInfo inf);
		void				AddLightToRender( Transform3D& tr, DirectionalLight* dl);
		void				AddParticlesSystemToRender( Transform3D& tr, ParticlesSystem *ps );


		// TODO 
		// Max pipelines reach
		template<typename T, typename ... Args>
		void AddPipeline( Args ... args );

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
		std::array<BasePipeline*, MAX_PIPELINES / 2>		_graphicPipelines{};
		std::array<BasePipeline*, MAX_PIPELINES / 2>		_computePipelines{};
		bool _changes;
		bool _isDefault;
		std::bitset<MAX_PIPELINES>					_createdPipeline;
	};
}
