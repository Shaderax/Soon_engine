#include "ECS/Component.hpp"

class DirectionalLight : public Component
{
	DirectionalLight( void ) : _direction(0.0f, -1.0f, 0.0f) {}
	~DirectionalLight( void ) {}
	public:
		vec3<float> _direction;
};
