#include "ECS/Component.hpp"
#include "Core/Math/vec3.hpp"
#include "Core/Math/vec2.hpp"

class TriangleRenderer : Component
{
	public:
		TriangleRenderer( void )
		{
			bool isRenderable = true;

			if (isRenderable)
				GraphicsRenderer::GetInstance()->AddToRender(this);
		};

		~TriangleRenderer( void );

	private:
		const float ui[] = {0.0f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f};
};

J'ai pas 36 possibilite, le but est qu'a la reconstruction du command buffer yai tous les vao/vbo qui sont contugue, il me faudra aussi au passage le transform de l'entity et donc un ptr sur le tr de l'entity, sauf que si c'est un vector et bah il va taper dans le transfor et peut etre que ca va faire n'importe quoi au niveau ducache donc faut que mes transform soit soit contigue soit que mes vao/vbo soit range par entity mais j peux pas car 


Si j'arrive avec id entity pour push dans vector.
