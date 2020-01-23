#include "spvReader.hpp"
#include <iostream>

int main()
{
	SpirvReader::GetShaderData("../Ressources/Shaders/DefaultShader.vert.spv");
	std::cout << std::endl;
	SpirvReader::GetShaderData("../Ressources/Shaders/DefaultShader.frag.spv");

	return (0);
}
