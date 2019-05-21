#pragma once

#include "Graphics/Vulkan/GraphicsInstance.hpp"
#include "Scene/3D/Components/Transform3D.hpp"
#include "Core/Math/mat4.hpp"

namespace Soon
{
	struct ComponentRenderer
	{
		std::vector< Transform3D* >::iterator		_transform;
		std::vector< VkBuffer >::iterator		_vkBuffers;
		std::vector< VkDeviceMemory >::iterator	_vkDevicesMemoryBuffers;
	};

	class GraphicsRenderer
	{
		static GraphicsRenderer* _instance;

		public:
		static GraphicsRenderer* GetInstance( void );
		GraphicsRenderer( void );
		ComponentRenderer AddToRender( Transform3D& tr, VertexBufferInfo inf);
		std::vector< VkBuffer > GetvkBuffers( void );
		std::vector< uint32_t > GetNbVertex( void );
		bool HasChange( void );
		void SetChangeFalse( void );

		private:
		std::vector< uint32_t >			_nbVertex;
		std::vector< Transform3D* >		_transform;
		std::vector< VkBuffer >			_vkBuffers;
		std::vector< VkDeviceMemory >		_vkDevicesMemoryBuffers;
		std::vector< mat4<float> >			_matrix;

		bool _changes;
	};
}
