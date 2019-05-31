#pragma once

#include "Graphics/Vulkan/GraphicsInstance.hpp"
#include "Scene/3D/Components/Transform3D.hpp"
#include "Core/Math/mat4.hpp"

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
			void 						Initialize( void );
			ComponentRenderer 			AddToRender( Transform3D& tr, VertexBufferInfo inf);
			std::vector< VkBuffer >		GetvkBuffers( void );
			std::vector< uint32_t >		GetNbVertex( void );
			bool						HasChange( void );
			void						SetChangeFalse( void );
			std::vector< BufferRenderer > GetUniformBuffers( void );
			std::vector< std::vector<VkDescriptorSet> > GetUniformsDescriptorSets( void );
			std::vector< Transform3D* > GetTransforms( void );
			UniformSets GetUniformsCamera( void );
			std::vector<VkDescriptorSet> GetUniformCameraDescriptorSets( void );

		private:
			std::vector< uint32_t >			_nbVertex;
			std::vector< Transform3D* >		_transforms;
			std::vector< VkBuffer >			_vkBuffers;
			std::vector< VkDeviceMemory >	_vkDevicesMemoryBuffers;

			// UNIFORM
			std::vector< BufferRenderer > 	_uniformsBuffers;
			std::vector< std::vector< VkDescriptorSet > >	_uniformsDescriptorSets;
			UniformSets						_uniformCamera;

			bool _changes;

	};
}
