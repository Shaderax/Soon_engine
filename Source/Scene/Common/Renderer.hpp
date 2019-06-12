#include "ECS/Component.hpp"
#include "Scene/Common/Material.hpp"

struct Renderer : public Component
{
	Renderer( void ) {};
	~Renderer( void ) {};

	Material _mat;
}
