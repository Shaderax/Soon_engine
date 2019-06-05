#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(set = 0, binding = 0) uniform UniformCamera
{
    mat4 view;
    mat4 proj;
} uc;

layout(set = 1, binding = 0) uniform UniformModel
{
    mat4 model;
} um;

layout(location = 0) in vec3 inPosition;

layout(location = 0) out vec3 fragColor;

void main()
{
	    gl_Position = uc.proj * uc.view * um.model * vec4(inPosition, 1.0);
	    fragColor = vec3(1.0f, 0.1f, 1.0f) * inPosition * 10;
}
