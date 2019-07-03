#pragma once

#include "ECS/Component.hpp"
#include "Core/Math/vec3.hpp"

#include "Scene/3D/Components/Transform3D.hpp"
#include "Graphics/Vulkan/GraphicsRenderer.hpp"

struct ParticlesSystem : public Component
{
	ParticlesSystem( Entity& entity ) : _size(10)
	{
		GraphicsRenderer::GetInstance()->AddParticlesToRender(entity.GetComponent<Transform3D>(), this);
	}

	~ParticlesSystem( void )
	{

	}

	uint32_t _size;

};
