#pragma once

#include "Graphics/Vulkan/GraphicsInstance.hpp"
#include "Scene/3D/Components/Transform3D.hpp"

namespace Soon
{
	struct ComponentRenderer
	{
		std::vector< Transform* >::iterator		_transform;
		std::vector< VkBuffer >::iterator		_vkBuffers;
		std::vector< VkDeviceMemory >::iterator	_vkDevicesMemoryBuffers;
	};

	class GraphicsRenderer
	{
		static GraphicsRenderer* _instance;

		public:
		static GraphicsRenderer* GetInstance( void );
		GraphicsRenderer( void );
		ComponentRenderer AddToRender( Transform* tr, VertexBufferInfo inf);
		std::vector< VkBuffer > GetvkBuffers( void );
		std::vector< size_t > GetNbVertex( void );
		bool HasChange( void );
		void SetChangeFalse( void );

		private:
		std::vector< std::size_t >		_nbVertex;
		std::vector< Transform* >		_transform;
		std::vector< VkBuffer >			_vkBuffers;
		std::vector< VkDeviceMemory >	_vkDevicesMemoryBuffers;

		bool _changes;
	};
}
