#pragma once


#ifndef MAT4_H
#define MAT4_H

#include "mat3.h"

namespace meow
{
	struct mat4
	{
		union
		{
			float m[16];
			float mm[4][4];
			vec4 c[4];
			struct 
			{
				union { vec4 c1; vec3 right; };
				union { vec4 c2; vec3 up; };
				union { vec4 c3; vec3 forward; };
				union { vec4 c4; vec3 position; };
			};
		};

		mat4 &operator=(const mat4 &a);

		mat4 &operator+=(const float &a);
		mat4 &operator+=(const mat4 &a);

		mat4 &operator-=(const float &a);
		mat4 &operator-=(const mat4 &a);

		mat4 &operator*=(const float &a);
		mat4 &operator*=(const mat4 &a);

		mat4 identity() const;
		mat4 inverse() const;
		mat4 transpose() const;
		//left = a, right = b, bottom = c, top = d, near = e, far = f
		mat4 orthographicProjection(const float &a, const float &b, const float &c, const float &d, const float &e, const float &f) const;
		mat4 rotate(const float &a, const int &b);
		//rotates around an arbitrary axis (true) or around x y z axis (false)
		mat4 rotate(const vec3 &a, const float &b, bool c = true);
		mat4 scale(const vec3 &a) const;
		mat4 translate(const vec3 &a) const;

		float determinant() const;

		mat3 minor(const int &a, const int &b) const;
	};

	mat4 operator+(const mat4 &a, const float &b);
	mat4 operator+(const float &a, const mat4 &b);
	mat4 operator+(const mat4 &a, const mat4 &b);

	mat4 operator-(const mat4 &a, const float &b);
	mat4 operator-(const mat4 &a, const mat4 &b);

	mat4 operator*(const mat4 &a, const float &b);
	mat4 operator*(const float &a, const mat4 &b);
	mat4 operator*(const mat4 &a, const mat4 &b);

	vec4 operator*(const mat4 &a, const vec4 &b);
	vec4 operator*(const vec4 &a, const mat4 &b);

	bool operator==(const mat4 &a, const mat4 &b);
	bool operator!=(const mat4 &a, const mat4 &b);
	bool operator<(const mat4 &a, const mat4 &b);
	bool operator<=(const mat4 &a, const mat4 &b);
	bool operator>(const mat4 &a, const mat4 &b);
	bool operator>=(const mat4 &a, const mat4 &b);

	std::ostream &operator<<(std::ostream &os, const mat4 &a);

	mat4 mat4Identity();
	mat4 inverse(const mat4 &a);
	mat4 transpose(const mat4 &a);
	//left = a, right = b, bottom = c, top = d, near = e, far = f
	mat4 orthographicProjection(const float &a, const float &b, const float &c, const float &d, const float &e, const float &f);
	mat4 rotate(const float &a, const int &b);
	//rotates around an arbitrary axis (true) or around x axis y axis z axis (false)
	mat4 rotate(const vec3 &a, const float &b, bool c = true);
	mat4 scale(const vec3 &a);
	mat4 translate(const vec3 &a);

	float determinant(const mat4 &a);

	mat4 mat3ToMat4(const mat3 &a);
	
	mat3 minor(const mat4 &a, const int &b, const int &c);
}



#endif