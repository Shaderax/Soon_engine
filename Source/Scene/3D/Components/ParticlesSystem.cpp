#include "Scene/3D/Components/ParticlesSystem.hpp"
#include "Scene/3D/Components/Transform3D.hpp"
#include "Graphics/Vulkan/GraphicsRenderer.hpp"

#include "ECS/ClassTypeId.hpp"

namespace Soon
{
	ParticlesSystem::ParticlesSystem( Entity& entity ) : _amount(100)
	{
		//		_shaderMaterial.SetPipeline<DefaultParticlesSystemPipeline>();
		_computeMaterial.SetPipeline<DefaultComputeParticlesSystemPipeline>();
		//		GraphicsRenderer::GetInstance()->AddParticlesSystemToRender(entity.GetComponent<Transform3D>(), this);
	}

	ParticlesSystem::~ParticlesSystem( void )
	{

	}

	template<typename T>
		void SetComponentToRender( T* cmp )
		{
			if (GetComponentTypeId<T>() == GetComponentTypeId<Mesh>())
				rt = ParticlesSystem::RenderType::MESH;
			else if (GetComponentTypeId<T>() == GetComponentTypeId<Sprite>())
				rt = ParticlesSystem::RenderType::SPRITE;
			else
			{
				std::cout << "Wrong Type for SetComponentToRender" << std::endl;
				return ;
			}
			_toRender = cmp;
			EnableRender();
		}

	void EnableRender( void )
	{
		if (_computeMaterial.bpipeline)
			_computeMaterial._computePipeline->AddToRender(cmp, _amount);
	}

	void DisableRender( void )
	{
		if (_computeMaterial.bpipeline)
			_computeMaterial._computePipeline->RemoveFromPipeline(cmp, _amount);
	}
}
