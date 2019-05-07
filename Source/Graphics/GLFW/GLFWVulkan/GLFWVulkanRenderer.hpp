#pragma once

class VulkanRenderer
{
	private:
		struct EntityRenderer
		{
			std::vector< BufferRenderer > Components;
		};

		std::vector< EntityRenderer > _entityRenderer;
};
