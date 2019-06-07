#!/bin/zsh

os=$(uname)

function darwin_env()
{
	export VK_ICD_FILENAMES=/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/MoltenVK/macOS/MoltenVK_icd.json
	export VK_LAYER_PATH=/Users/nrouzeva/Documents/42_PJ/Soon_engine/ThirdParty/vulkan/Validation_Layer/explicit_layer.d/macos/
}

function linux_env()
{
	export VK_LAYER_PATH=/home/shaderax/Documents/Project/Soon_engine/ThirdParty/vulkan/Validation_Layer/explicit_layer.d/linux/
}

case $os in
	"Darwin")
		darwin_env ;;
	"Linux")
		linux_env ;;
	*)
		"We don't want window !";
esac
