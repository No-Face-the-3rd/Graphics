#pragma once


#ifndef VEC3_H
#define VEC3_H

#include "vec2.h"

namespace meow
{
	struct vec3
	{
		union
		{
			float v[3];
			struct {float x, y, z; };
			struct {vec2 xy;float z;};
		};

		vec3 &operator=(const float &a);
		vec3 &operator=(const vec2 &a);
		vec3 &operator=(const vec3 &a);

		vec3 &operator+=(const float &a);
		vec3 &operator+=(const vec2 &a);
		vec3 &operator+=(const vec3 &a);

		vec3 &operator-=(const float &a);
		vec3 &operator-=(const vec2 &a);
		vec3 &operator-=(const vec3 &a);

		vec3 &operator*=(const float &a);
		
		vec3 &operator/=(const float &a);

		vec3 normal() const;
		void normalize();
		float magnitude() const;
		float dot(const vec3 &a) const;
		vec3 cross(const vec3 &a) const;
		vec3 lerp(const vec3 &a, const float &b) const;
		vec3 reflection(const vec3 &a) const;

	};
	vec3 operator+(const vec3 &a, const float &b);
	vec3 operator+(const float &a, const vec3 &b);
	vec3 operator+(const vec3 &a, const vec2 &b);
	vec3 operator+(const vec2 &a, const vec3 &b);
	vec3 operator+(const vec3 &a, const vec3 &b);

	vec3 operator-(const vec3 &a, const float &b);
	vec3 operator-(const vec3 &a, const vec2 &b);
	vec3 operator-(const vec3 &a, const vec3 &b);

	vec3 operator-(const vec3 &a);

	vec3 operator*(const vec3 &a, const float &b);
	vec3 operator*(const float &a, const vec3 &b);

	vec3 operator/(const vec3 &a, const float &b);

	bool operator==(const vec3 &a, const vec3 &b);
	bool operator!=(const vec3 &a, const vec3 &b);
	bool operator<(const vec3 &a, const vec3 &b);
	bool operator<=(const vec3 &a, const vec3 &b);
	bool operator>(const vec3 &a, const vec3 &b);
	bool operator>=(const vec3 &a, const vec3 &b);

	std::ostream &operator<<(std::ostream &os, const vec3 &p);

	vec3 normal(const vec3 &a);
	void normalize(vec3 &a);
	float magnitude(const vec3 &a);
	float dot(const vec3 &a, const vec3 &b);
	vec3 cross(const vec3 &a, const vec3 &b);
	vec3 lerp(const vec3 &a, const vec3 &b, const float &c);
	vec3 reflection(const vec3 &a, const vec3 &b);

}
#endif