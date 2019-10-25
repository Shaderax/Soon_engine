#pragma once

#include "Core/Scene/Common/Texture2D.hpp"
#include "Core/Scene/ComponentRenderer.hpp"

namespace Soon
{
	class Sprite : Texture2D, ComponentRenderer
	{
		public:
			void EnableRender() {};
			void DisableRender() {};
	};
}
