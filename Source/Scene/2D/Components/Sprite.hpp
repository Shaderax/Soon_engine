#pragma once

#include "Scene/Common/Texture2D.hpp"
#include "Scene/ComponentRenderer.hpp"

namespace Soon
{
	class Sprite : Texture2D, ComponentRenderer
	{
		public:
			void EnableRender() {};
			void DisableRender() {};
	};
}
