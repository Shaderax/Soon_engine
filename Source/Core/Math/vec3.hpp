#pragma once

#include <math.h>

template< typename T = float >
class vec3
{
	public :
		vec3( void ) {};
		~vec3( void ) {};

		T x;
		T y;
		T z;
		
		vec3(T mx, T my, T mz) : x(mx), y(my), z(mz)
		{
			
		}

		vec3<T> operator+(vec3<T> const& b)
		{
			vec3 Result;

			Result.x = this->x + b.x;
			Result.y = this->y + b.y;
			Result.z = this->z + b.z;

			return (Result);
		}

		vec3<T> operator-(vec3<T> const& b)
		{
			vec3 Result;

			Result.x = this->x - b.x;
			Result.y = this->y - b.y;
			Result.z = this->z - b.z;

			return (Result);
		}

		vec3<T>& operator+=(vec3<T> const& b)
		{
			this->x += b.x;
			this->y += b.y;
			this->z += b.z;

			return (*this);
		}

		vec3<T>& operator-=(vec3<T> const& b)
		{
			this->x -= b.x;
			this->y -= b.y;
			this->z -= b.z;

			return (*this);
		}

		vec3<T>& operator=(vec3<T> const& b)
		{
			this->x = b.x;
			this->y = b.y;
			this->z = b.z;

			return (*this);
		}

		vec3<T> Cross(vec3<T> const& a)
		{
			vec3 Result;

			Result.x = this->y * a.z - this->z * a.y;
			Result.y = this->z * a.x - this->x * a.z;
			Result.z = this->x * a.y - this->y * a.x;

			return (Result);
		}

		float Magnitude( void )
		{
			return (sqrt((x * x) + (y * y) + (z * z)));
		}

		void	Normalize( void )
		{
			float mag;

			mag = this->Magnitude();
			if (mag == 0.0f)
				return ;
			this->x /= mag;
			this->y /= mag;
			this->z /= mag;
		}

};
