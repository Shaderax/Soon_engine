#include "Scene/3D/Components/ParticlesSystem.hpp"
#include "Scene/3D/Components/Transform3D.hpp"
#include "Graphics/Vulkan/GraphicsRenderer.hpp"

namespace Soon
{
	ParticlesSystem::ParticlesSystem( Entity& entity ) : _size(100000)
	{
		GraphicsRenderer::GetInstance()->AddParticlesSystemToRender(entity.GetComponent<Transform3D>(), this);
	}

	ParticlesSystem::~ParticlesSystem( void )
	{

	}
}
