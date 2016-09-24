#pragma once


#ifndef VEC2_H
#define VEC2_H

#include <iostream>
#include <cmath>
#include <cfloat>
#include <algorithm>

#define FLT_EPSILON 0.00001

namespace meow
{
	struct vec2
	{
		union
		{
			float v[2];
			struct { float x, y; };
		};


		vec2 &operator=(const float &a);
		vec2 &operator=(const vec2 &a);

		vec2 &operator+=(const float &a);
		vec2 &operator+=(const vec2 &a);

		vec2 &operator-=(const float &a);
		vec2 &operator-=(const vec2 &a);

		vec2 &operator*=(const float &a);

		vec2 &operator/=(const float &a);

		vec2 normal() const;
		void normalize();
		float magnitude() const;
		float dot(const vec2 &a) const;
		vec2 perpendicular() const;
		float angle() const;
		vec2 lerp(const vec2 &a, const float &b) const;
		vec2 reflection(const vec2 &a) const;
	};

	vec2 operator+(const vec2 &a, const vec2 &b);
	vec2 operator+(const vec2 &a, const float &b);
	vec2 operator+(const float &a, const vec2 &b);

	vec2 operator-(const vec2 &a, const vec2 &b);
	vec2 operator-(const vec2 &a, const float &b);

	vec2 operator-(const vec2 &a);

	vec2 operator*(const vec2 &a, const float &b);
	vec2 operator*(const float &a, const vec2 &b);

	vec2 operator/(const vec2 &a, const float &b);

	bool operator==(const vec2 &a, const vec2 &b);
	bool operator!=(const vec2 &a, const vec2 &b);
	bool operator<(const vec2 &a, const vec2 &b);
	bool operator<=(const vec2 &a, const vec2 &b);
	bool operator>(const vec2 &a, const vec2 &b);
	bool operator>=(const vec2 &a, const vec2 &b);

	std::ostream &operator<<(std::ostream &os, const vec2 &p);

	vec2 normal(const vec2 &a);
	void normalize(vec2 &a);
	float magnitude(const vec2 &a);
	vec2 perpendicular(const vec2 &a);
	float dot(const vec2 &a, const vec2 &b);
	float angle(const vec2 &a);
	vec2 lerp(const vec2 &a, const vec2 &b, const float &c);
	vec2 reflection(const vec2 &a, const vec2 &b);
}


#endif