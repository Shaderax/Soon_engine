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
			ComponentRenderer 			AddToRender( Transform3D& tr, VertexBufferInfo inf);
			std::vector< VkBuffer >		GetvkBuffers( void );
			std::vector< uint32_t >		GetNbVertex( void );
			bool						HasChange( void );
			void						SetChangeFalse( void );

		private:
			std::vector< uint32_t >			_nbVertex;
			std::vector< Transform3D* >		_transform;
			std::vector< VkBuffer >			_vkBuffers;
			std::vector< VkDeviceMemory >	_vkDevicesMemoryBuffers;

			struct UniformRender
			{
				std::vector<VkBuffer>		_Buffer;
				std::vector<VkDeviceMemory>	_BufferMemory;
			};

			std::vector< UniformRender > _uniforms;

			bool _changes;

			std::vector< UniformRender > _uniformCamera;
	};
}
