#include "Graphics/Vulkan/GraphicsRenderer.hpp"
#include "Graphics/Vulkan/GraphicsInstance.hpp"
#include "Scene/3D/Components/Transform3D.hpp"

namespace Soon
{
		GraphicsRenderer* GraphicsRenderer::_instance = nullptr;

		GraphicsRenderer* GraphicsRenderer::GetInstance( void )
		{
			return (_instance);
		}

		GraphicsRenderer::GraphicsRenderer( void ) : _changes(false)
		{
			_instance = this;
		}

		ComponentRenderer GraphicsRenderer::AddToRender( Transform* tr, VertexBufferInfo inf)
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

		std::vector< VkBuffer > GraphicsRenderer::GetvkBuffers( void )
		{
			return (_vkBuffers);
		}

		std::vector< size_t > GraphicsRenderer::GetNbVertex( void )
		{
			return (_nbVertex);
		}

		bool GraphicsRenderer::HasChange( void )
		{
			return (_changes);
		}

		void GraphicsRenderer::SetChangeFalse( void )
		{
			_changes = false;
		}
}
