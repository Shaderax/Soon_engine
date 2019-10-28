#pragma once

#include "Core/Scene/Common/Texture2D.hpp"
#include "Core/Scene/ComponentRenderer.hpp"

namespace Soon
{
	class Sprite : ComponentRenderer
	{
		Mesh		_mesh;
		Texture2D*	_texture;

		public:
		Sprite( void )
		{
			MeshArray* arr = RessourceImporter::GetSingleton()->Load<Soon::MeshArray>("../Ressources/Objects/Basics/Quad.obj");
			_texture = RessourceImporter::GetSingleton()->Load<Soon::Texture2D>("../Ressources/Textures/Aude.png");
		}
			void EnableRender() {};
			void DisableRender() {};
	};
}
