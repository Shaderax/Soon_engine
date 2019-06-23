#include "Graphics/Pipelines/BasePipeline.hpp"

class DefaultParticlesSystemPipeline : public BasePipeline
{
	std::vector< Transform3D* >		_transforms;
	std::vector< VkBuffer >			_gpuBuffers;
	std::vector< VkDeviceMemory >	_gpuMemoryBuffers;
};
