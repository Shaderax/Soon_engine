class BasePipeline
{
	virtual std::array<VkDescriptorSetLayoutBinding> GetLayoutBinding( void );
	virtual VkVertexInputBindingDescription GetBindingDescription( void );
	virtual void UpdateData( int currentImg );
	virtual void BindCaller( VkCommandBuffer commandBuffer );
	virtual std::array<VkVertexInputAttributeDescription> GetAttributeDescriptions( void );

	std::vector<VkDescriptorSetLayout>		_descriptorSetLayout;
	VkPipelineLayout 				_pipelineLayout;
	VkPipeline					_graphicsPipeline;

	struct Properties
	{
		
	} _properties;
};
