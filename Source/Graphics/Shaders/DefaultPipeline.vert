#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(set = 0, binding = 0) uniform UniformCamera
{
	mat4 view;
	mat4 proj;
} uc;

void main()
{
	gl_Position = uc.proj * uc.view * vec4(1.0f);
}
