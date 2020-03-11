#pragma once

#include "ECS/Entity.hpp"
#include "ECS/Component.hpp"
#include "Core/Scene/Materials/ShaderMaterial.hpp"

namespace Soon
{
	ComponentRenderer::ComponentRenderer( void )
	{

	}

	ComponentRenderer::~ComponentRenderer( void )
	{
	}

	void ComponentRenderer::Enable( void )
	{
		if (!IsActivated())
		{
        	Entity owner(_ownerId);
       		owner.EnableComponent( _componentId );

			_material.Render(_owner->GetComponent<Transform3D>(), owner.GetComponent(_componentId));
		}
	}

	void ComponentRenderer::Disable( void )
	{
		if (IsActivated())
		{
        	Entity owner(_ownerId);
        	owner.DisableComponent( _componentId );

			_material.UnRender(_id);
		}
	}
};