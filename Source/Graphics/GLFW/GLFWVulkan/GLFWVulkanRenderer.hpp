#pragma once

class GLFWVulkanRenderer
{
	public:
		std::vector<ComponentRenderer>::iterator VulkanRenderer::AddToRender( Transform* tr, VertexBufferInfo inf)
		{
			BufferRenderer handler;

			handler = GraphicsInstance::GetInstance()->CreateVertexBuffer(inf);

			_componentRenderer.emplace_back(handler, tr);

			return _componentRenderer.end();
		}

		std::vector< ComponentRenderer > GetvkBuffers( void )
		{
			return (_vkBuffers);
		}

		std::vector< ComponentRenderer > GetvkDeviceMemory( void )
		{
			return (_vkDevicesMemoryBuffers);
		}

		std::vector< ComponentRenderer > GetTransform( void )
		{
			return (_transform);
		}

	private:
		std::vector< Transform* >		_transform;
		std::vector< VkBuffer >			_vkBuffers;
		std::vector< VkDeviceMemory >	_vkDevicesMemoryBuffers;
};
