#ifndef MATLIBHEADER_HPP
# define MATLIBHEADER_HPP

# include "math.h"
# define PI 3.14159265358979323846

class Vector3
{
	public :
		float x;
		float y;
		float z;

		Vector3( void );
		~Vector3( void );

		Vector3& operator+=(const Vector3& rhs)
		{
			for(int i = 0; i < 16; i++)
			{
				this->m_elements[i] += rhs.m_elements[i];
			}
			return *this;
		}

		inline Matrix4x4& operator-=(const Matrix4x4& rhs)
		{
			for(int i = 0; i < 16; i++)
			{
				this->m_elements[i] -= rhs.m_elements[i];
			}
			return *this;
		}

		inline Matrix4x4& operator*=(const Matrix4x4& rhs)
		{
			this->m_elements[0] = this->m_elements[0] * rhs.m_elements[0] + this->m_elements[1] * rhs.m_elements[4] + this->m_elements[2] * rhs.m_elements[8] + this->m_elements[3] * rhs.m_elements[12];
			this->m_elements[1] = this->m_elements[0] * rhs.m_elements[1] + this->m_elements[1] * rhs.m_elements[5] + this->m_elements[2] * rhs.m_elements[9] + this->m_elements[3] * rhs.m_elements[13];
			this->m_elements[2] = this->m_elements[0] * rhs.m_elements[2] + this->m_elements[1] * rhs.m_elements[6] + this->m_elements[2] * rhs.m_elements[10] + this->m_elements[3] * rhs.m_elements[14];
			this->m_elements[3] = this->m_elements[0] * rhs.m_elements[3] + this->m_elements[1] * rhs.m_elements[7] + this->m_elements[2] * rhs.m_elements[11] + this->m_elements[3] * rhs.m_elements[15];
		}

		inline Matrix4x4& operator*=(const GLfloat& rhs)
		{
			for(int i = 0; i < 16; i++)
			{
				this->m_elements[i] *= rhs;
			}
			return *this;
		}
}

class Vector4
{
	public :
		float x;
		float y;
		float z;
		float w;

		Vector4( void );
		~Vector4( void );
}

class Mat4
{
	public :
		float elements[4][4];

		Mat4( void );
		~Mat4( void );
}

void    vec3_add(t_vec3 vector1, t_vec3 vector2, t_vec3 vector3);
void    vec3_sub(t_vec3 vector1, t_vec3 vector2, t_vec3 vector3);
void    vec3_cross(t_vec3 vector1, t_vec3 vector2, t_vec3 vector3);
void    vec3_norm(t_vec3 vec);

void    vec4_add(t_vec4 vector1, t_vec4 vector2, t_vec4 vector3);
void    vec4_sub(t_vec4 vector1, t_vec4 vector2, t_vec4 vector3);
void    vec4_mul(t_vec4 vector1, t_vec4 vector2, t_vec4 vector3);
void    vec4_cross(t_vec4 vector1, t_vec4 vector2, t_vec4 vector3);
void    vec4_norm(t_vec4 vec);
void    vec4_set(t_vec4 vector1, t_vec4 vector2);
void    vec4_mul_scal(t_vec4 vec, float i, t_vec4 ret);

void    mat4_set(t_mat4 mat);
void    mat4_mul(t_mat4 mat1, t_mat4 mat2, t_mat4 ret);
void    mat4_sub(t_mat4 mat1, t_mat4 mat2, t_mat4 ret);
void    mat4_add(t_mat4 mat1, t_mat4 mat2, t_mat4 ret);
void    mat4_translate(t_mat4 mat1, t_vec4 vec, t_mat4 mat2);
void    mat4_rotate(t_mat4 mat1, float angle, int axis, t_mat4 mat2);

#endif
