#pragma once

#include "ECS/Entity.hpp"
#include "Core/Scene/ComponentRenderer.hpp"

#include "Core/Scene/Materials/ComputeMaterial.hpp"

namespace Soon
{
	class Mesh;
	struct ParticlesSystem : public ComponentRenderer
	{
		public:

		enum class RenderType : uint32_t
		{
			NONE = 0,
			MESH = 1,
			SPRITE = 2
		};

		ParticlesSystem( Entity& entity );

		~ParticlesSystem( void );

//	template<typename T>
		void SetComponentToRender( Mesh* cmp );

		void EnableRender( void );
		void DisableRender( void );

		uint32_t		_amount;
		RenderType		_rt;
		Mesh*			_toRender;
		ComputeMaterial		_computeMaterial;
	};
}
