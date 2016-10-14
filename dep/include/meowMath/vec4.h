#pragma once

#ifndef VEC4_H
#define VEC4_H

#include "vec3.h"

namespace meow
{
	struct vec4
	{
		union
		{
			float v[4];
			struct { float x, y, z, w; };
			struct { float r, g, b, a; };
			struct { vec3 xyz; float w; };
			struct { vec2 xy; vec2 zw; };
		};
		
		vec4 &operator=(const float &a);
		vec4 &operator=(const vec2 &a);
		vec4 &operator=(const vec3 &a);
		vec4 &operator=(const vec4 &a);

		vec4 &operator+=(const float &a);
		vec4 &operator+=(const vec2 &a);
		vec4 &operator+=(const vec3 &a);
		vec4 &operator+=(const vec4 &a);

		vec4 &operator-=(const float &a);
		vec4 &operator-=(const vec2 &a);
		vec4 &operator-=(const vec3 &a);
		vec4 &operator-=(const vec4 &a);

		vec4 &operator*=(const float &a);

		vec4 &operator/=(const float &a);

		vec4 normal() const;
		void normalize();
		float magnitude() const;
		float dot(const vec4 &a) const;
		vec4 lerp(const vec4 &a, const float &b) const;
		vec4 reflection(const vec4 &a) const;
	};
	vec4 operator+(const vec4 &a, const float &b);
	vec4 operator+(const float &a, const vec4 &b);
	vec4 operator+(const vec4 &a, const vec2 &b);
	vec4 operator+(const vec2 &a, const vec4 &b);
	vec4 operator+(const vec4 &a, const vec3 &b);
	vec4 operator+(const vec3 &a, const vec4 &b);
	vec4 operator+(const vec4 &a, const vec4 &b);

	vec4 operator-(const vec4 &a, const float &b);
	vec4 operator-(const vec4 &a, const vec2 &b);
	vec4 operator-(const vec4 &a, const vec3 &b);
	vec4 operator-(const vec4 &a, const vec4 &b);

	vec4 operator-(const vec4 &a);

	vec4 operator*(const vec4 &a, const float &b);
	vec4 operator*(const float &a, const vec4 &b);

	vec4 operator/(const vec4 &a, const float &b);

	bool operator==(const vec4 &a, const vec4 &b);
	bool operator!=(const vec4 &a, const vec4 &b);
	bool operator<(const vec4 &a, const vec4 &b);
	bool operator<=(const vec4 &a, const vec4 &b);
	bool operator>(const vec4 &a, const vec4 &b);
	bool operator>=(const vec4 &a, const vec4 &b);

	std::ostream &operator<<(std::ostream &os, const vec4 &p);

	vec4 normal(const vec4 &a);
	void normalize(vec4 &a);
	float magnitude(const vec4 &a);
	float dot(const vec4 &a, const vec4 &b);
	vec4 lerp(const vec4 &a, const vec4 &b, const float &c);
	vec4 reflection(const vec4 &a, const vec4 &b);
}


#endif