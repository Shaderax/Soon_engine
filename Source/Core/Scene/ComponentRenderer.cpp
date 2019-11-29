#pragma once

#include "ECS/Entity.hpp"
#include "ECS/Component.hpp"
#include "Core/Scene/Materials/ShaderMaterial.hpp"

namespace Soon
{
	ComponentRenderer::ComponentRenderer( void ) : _active(false), _owner(nullptr)
	{

	}

	ComponentRenderer::~ComponentRenderer( void )
	{

	}

	void ComponentRenderer::Enable( void )
	{
		if (_owner)
			_material.Render(_owner->GetComponent<Transform3D>(), _owner->GetComponent<Mesh>());
	}

	void ComponentRenderer::Disable( void )
	{
		_material.UnRender();
	}
};
