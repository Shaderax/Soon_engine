#pragma once

struct UniformCamera
{
	alignas(16) mat4<float> view;
	alignas(16) mat4<float> proj;
};

struct UniformModel
{
	alignas(16) mat4<float> model;
};

struct UniformMaterial
{
	alignas(16)	vec3<float>		_ambient;
	alignas(16)	vec3<float>		_diffuse;
	alignas(16)	vec3<float>		_specular;
	alignas(4)	float			_shininess;
};

struct UniformLight
{
	alignas(16) vec3<float> _direction;
	alignas(16) vec3<float> _lightColor;
	alignas(4) float _intensity;
};

