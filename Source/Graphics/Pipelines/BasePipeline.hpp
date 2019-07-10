#pragma once

struct BasePipeline
{
	BasePipeline()
	{

	}

	virtual ~BasePipeline() {}
	virtual std::vector<VkDescriptorSetLayoutBinding> GetLayoutBinding( void ) = 0;
	virtual VkVertexInputBindingDescription GetBindingDescription( void );
	virtual void UpdateData( int currentImg ) = 0;
	virtual void BindCaller( VkCommandBuffer commandBuffer, uint32_t index ) = 0;
	virtual std::vector<VkVertexInputAttributeDescription> GetAttributeDescriptions( void );
	virtual void RecreateUniforms( void ) = 0;

	std::vector<VkDescriptorSetLayout>		_descriptorSetLayout;
	VkPipelineLayout 						_pipelineLayout;
	VkPipeline								_graphicPipeline;

	struct Properties
	{
		
	};
};
