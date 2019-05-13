#pragma once

#include "Graphics/Vulkan/GraphicsInstance.hpp"

struct ComponentRenderer
{
	std::vector< Transform* >::iterator		_transform;
	std::vector< VkBuffer >::iterator		_vkBuffers;
	std::vector< VkDeviceMemory >::iterator	_vkDevicesMemoryBuffers;
}

class GraphicsRenderer
{
	static GraphicsRenderer* _instance;

	public:
		static GLFWVulkanRenderer* GetInstance( void )
		{
			return (_instance);
		}

		GraphicsRenderer( void ) : _changes(false)
		{
			_instance = this;
		}

		ComponentRenderer VulkanRenderer::AddToRender( Transform* tr, VertexBufferInfo inf)
		{
			BufferRenderer handler;
			ComponentRenderer ret;

			handler = GraphicsInstance::GetInstance()->CreateVertexBuffer(inf);

			_nbVertex.push_back(inf._nbVertex);
			_transform.push_back(tr);
			_vkBuffers.push_back(handler._vertexBuffer);
			_vkDevicesMemoryBuffers.push_back(handler._vertexBufferMemory);

			ret._transform = _transform.end();
			ret._vkBuffers = _vkBuffers.end();
			ret._vkDevicesMemoryBuffers = _vkDevicesMemoryBuffers.end();

			_changes = true;
			return ret;
		}

		std::vector< VkBuffer > GetvkBuffers( void )
		{
			return (_vkBuffers);
		}
		
		std::vector< size_t > GetNbVertex( void )
		{
			return (_nbVertex);
		}

		bool GLFWVulkanRenderer::HasChange( void )
		{
			return (_changes);
		}
		
		void GLFWVulkanRenderer::SetChangeFalse( void )
		{
			_changes = false;
		}

	private:
		std::vector< std::size_t >		_nbVertex;
		std::vector< Transform* >		_transform;
		std::vector< VkBuffer >			_vkBuffers;
		std::vector< VkDeviceMemory >	_vkDevicesMemoryBuffers;

		bool _changes;
};
