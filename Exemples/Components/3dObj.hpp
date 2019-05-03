#include "ECS/Component.hpp"
#include "Core/Math/vec3.hpp"
#include "Core/Math/vec2.hpp"

class 3dObj : Component
{
	public:
		3dObj( void );
		~3dObj( void );

	private:
		const float[] = {0.0f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f};
		std::vector<vec3> v;
		std::vector<vec2> vt;
		std::vector<vec3> vn;

		static VkVertexInputBindingDescription getBindingDescription()
		{
			VkVertexInputBindingDescription bindingDescription = {};
			bindingDescription.binding = 0;
			bindingDescription.stride = sizeof(float) * 2; // stride : size of one pointe
			bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

			return bindingDescription;
		}

		static std::array<VkVertexInputAttributeDescription, 1> getAttributeDescriptions()
		{
			std::array<VkVertexInputAttributeDescription, 1> attributeDescriptions = {};

			attributeDescriptions[0].binding = 0;
			attributeDescriptions[0].location = 0;
			attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
			attributeDescriptions[0].offset = 0//offsetof(Vertex, pos);

//			attributeDescriptions[1].binding = 0;
//			attributeDescriptions[1].location = 1;
//			attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
//			attributeDescriptions[1].offset = offsetof(Vertex, color);

			return attributeDescriptions;
		}
};
