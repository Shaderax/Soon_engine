#include "Core/Math/vec2.hpp"
#include "Core/Math/vec3.hpp"
#include "Scene/3D/Components/Mesh.hpp"
#include <cstring>
#include "Scene/Object.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Scene/Common/ObjectOwner.hpp"

#include "Graphics/Pipelines/DefaultVertexPipeline.hpp"

namespace Soon
{
	void Mesh::EnableRender( void )
	{
		GraphicsRenderer::GetInstance()->AddVertexToRender(_owner->GetComponent<Transform3D>(), _inf);
//		for (Object& obj : _owner.GetComponent<ObjectOwner>()._owner->GetChildrens())
//			obj.EnableRender();
	}

	void Mesh::DisableRender( void )
	{

	}
};
