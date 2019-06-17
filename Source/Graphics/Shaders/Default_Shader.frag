#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0, set = 2) uniform sampler2D texSampler;

layout(set = 3, binding = 0) uniform UniformMaterial
{
	vec3	_ambient;
	vec3	_diffuse;
	vec3	_specular;
	float	_shininess;
} um;

layout(set = 4, binding = 0) uniform UniformLight
{
	vec3 _direction;
	vec3 _lightColor;
	float _intensity;
} ul;

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

void main()
{

	float ambientStrength = 1.0;
//    vec3 ambient = ambientStrength/* * ul._lightColor*/;

	vec3 result = ambientStrength * um._ambient;

    outColor = vec4(result, 1.0f) * texture(texSampler, fragTexCoord);
}
