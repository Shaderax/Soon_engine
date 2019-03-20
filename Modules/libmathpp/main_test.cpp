#include <stdio.h>
#include "vec3.hpp"
#include "vec4.hpp"
#include "mat4.hpp"

int main( void )
{
	vec3<float> Vector0;
	Vector0.x = 10.0f;

	vec3<float> Vector1;
	Vector1.x = 20.0f;

	Vector0 += Vector1;
	printf("%f\n", Vector0.x);

	vec4<float> Vector2;
	vec4<float> Vector3;
	vec4<float> Vector4;
	Vector2.x = 10.0f;
	Vector3.x = 15.0f;
	Vector4 = Vector2 - Vector3;
	Vector2 -= Vector3;
	printf("%f, %f\n", Vector2.x, Vector4.x);

	mat4<float> matrix;
	printf("%f\n", matrix(1, 0));
	printf("%f\n", matrix(1, 1));
}
