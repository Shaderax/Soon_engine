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
		T* AddPipeline( Args ... args );

		template<typename T>
		void RemovePipeline( void );

		private:
		std::array<BasePipeline*, MAX_PIPELINES / 2>		_graphicPipelines{};
		std::array<BasePipeline*, MAX_PIPELINES / 2>		_computePipelines{};
		bool _changes;
		std::bitset<MAX_PIPELINES>					_createdPipeline;
	};
}
