#pragma once


#ifndef MAT3_H
#define MAT3_H

#include "vec4.h"

#define PI 3.14159265358979323846264338327950288419716939937510f

namespace meow
{
	struct mat3
	{
		union
		{
			float m[9];
			float mm[3][3];
			vec3 c[3];
			struct 
			{
				union { vec3 c1; vec2 right; };
				union { vec3 c2; vec2 up; };
				union { vec3 c3; vec2 position; };
			};
		};

		mat3 &operator=(const mat3 &a);

		mat3 &operator+=(const float &a);
		mat3 &operator+=(const mat3 &a);

		mat3 &operator-=(const float &a);
		mat3 &operator-=(const mat3 &a);

		mat3 &operator*=(const float &a);
		mat3 &operator*=(const mat3 &a);

		mat3 identity() const;
		mat3 inverse() const;
		mat3 transpose() const;
		mat3 rotate(const float &a) const;
		mat3 rotate(const vec2 &a) const;
		mat3 scale(const vec2 &a) const;
		mat3 translate(const vec2 &a) const;
		
		float determinant() const;
	};
	
	mat3 operator+(const mat3 &a, const float &b);
	mat3 operator+(const float &a, const mat3 &b);
	mat3 operator+(const mat3 &a, const mat3 &b);

	mat3 operator-(const mat3 &a, const float &b);
	mat3 operator-(const mat3 &a, const mat3 &b);

	mat3 operator*(const mat3 &a, const float &b);
	mat3 operator*(const float &a, const mat3 &b);
	mat3 operator*(const mat3 &a, const mat3 &b);

	vec3 operator*(const mat3 &a, const vec3 &b);
	vec3 operator*(const vec3 &a, const mat3 &b);

	bool operator==(const mat3 &a, const mat3 &b);
	bool operator!=(const mat3 &a, const mat3 &b);
	bool operator<(const mat3 &a, const mat3 &b);
	bool operator<=(const mat3 &a, const mat3 &b);
	bool operator>(const mat3 &a, const mat3 &b);
	bool operator>=(const mat3 &a, const mat3 &b);

	std::ostream &operator<<(std::ostream &os, const mat3 &a);

	mat3 mat3Identity();
	mat3 inverse(const mat3 &a);
	mat3 transpose(const mat3 &a);
	mat3 rotate(const float &a);
	mat3 rotate(const vec2 &a);
	mat3 scale(const vec2 &a);
	mat3 translate(const vec2 &a);

	float determinant(const mat3 &a);
}



#endif