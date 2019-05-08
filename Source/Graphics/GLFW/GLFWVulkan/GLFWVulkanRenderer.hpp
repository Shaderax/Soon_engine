#pragma once

class VulkanRenderer
{
	public:
		BufferRenderer VulkanRenderer::AddToRender( uint32_t id )
		{
			BufferRenderer handler;

			handler = GraphicsInstance::GetInstance()->CreateVertexBuffer(24);

			_entityRenderer.push_back(handler);

			return handler;
		}

	private:
		struct EntityRenderer
		{
			Transform* tr;
			std::vector< BufferRenderer > Components;
		};

		std::vector< EntityRenderer > _entityRenderer;
};
