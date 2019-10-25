#include "ParticlesSystem.hpp"
#include "Transform3D.hpp"

#include "ECS/ClassTypeId.hpp"

#include "../..//2D/Components/Sprite.hpp"
#include "Mesh.hpp"

namespace Soon
{
	ParticlesSystem::ParticlesSystem( Entity& entity ) : _amount(100)
	{
		//		_shaderMaterial.SetPipeline<DefaultParticlesSystemPipeline>();
//		_computeMaterial.SetPipeline<DefaultComputeParticlesSystemPipeline>();
		//		GraphicsRenderer::GetInstance()->AddParticlesSystemToRender(entity.GetComponent<Transform3D>(), this);
	}

	ParticlesSystem::~ParticlesSystem( void )
	{

	}

//	template<typename T>
		void ParticlesSystem::SetComponentToRender( Mesh* cmp )
		{
//			if (GetComponentTypeId<T>() == GetComponentTypeId<Mesh>())
//				_rt = ParticlesSystem::RenderType::MESH;
//			else if (GetComponentTypeId<T>() == GetComponentTypeId<Sprite>())
//				_rt = ParticlesSystem::RenderType::SPRITE;
//			else
//			{
//				std::cout << "Wrong Type for SetComponentToRender" << std::endl;
//				return ;
//			}
			_toRender = cmp;
			EnableRender();
		}

	void ParticlesSystem::EnableRender( void )
	{
		//if (_computeMaterial._computePipeline)
		//	_computeMaterial._computePipeline->AddToRender(_toRender, _amount);
	}

	void ParticlesSystem::DisableRender( void )
	{
//		if (_computeMaterial._computePipeline)
//			_computeMaterial._computePipeline->RemoveFromPipeline(_toRender, _amount);
	}
}
