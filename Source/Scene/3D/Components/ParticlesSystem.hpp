#include "ECS/Component.hpp"
#include "Core/Math/vec3.hpp"

struct ParticlesSystem : public Component
{
	ParticlesSystem( void ) : _size(10)
	{
		GraphicsRenderer::GetInstance()->AddToRender();
	}

	~ParticlesSystem( void )
	{

	}

	uint32_t _size;

};
