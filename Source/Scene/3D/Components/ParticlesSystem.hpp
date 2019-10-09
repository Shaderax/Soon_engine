#pragma once

#include "ECS/Entity.hpp"
#include "Scene/ComponentRenderer.hpp"

namespace Soon
{
	struct ParticlesSystem : public ComponentRenderer
	{
		public:

		enum class RenderType : uint32_t
		{
			NONE = 0,
			MESH = 1,
			SPRITE = 2;
		};

		ParticlesSystem( Entity& entity );

		~ParticlesSystem( void );

		uint32_t		_amount;
		RenderType		_rt;
		ComponentRenderer*	_toRender;
		ComputeMaterial		_computeMaterial;
	};
}
