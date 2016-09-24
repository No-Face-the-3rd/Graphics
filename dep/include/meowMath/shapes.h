#pragma once

#ifndef SHAPES
#define SHAPES

#include "mat4.h"

#include <vector>
namespace meow
{


	struct aabb
	{
		meow::vec2 pos, dim;

		meow::vec2 min() const;
		meow::vec2 max() const;

		static aabb genaabb(const std::vector<meow::vec2>& corners);

		void rotate(float a);
	};
	struct circle
	{
		meow::vec2 pos;
		float rad;
	};
	struct convexHull 
	{
		std::vector<meow::vec2> verts;
	};
	struct plane
	{
		meow::vec2 pos, normal;	
	};
	struct ray 
	{
		meow::vec2 pos, dir;
		float length;
	};
	aabb operator*(const meow::mat3 &a, const meow::aabb &b);
	circle operator*(const meow::mat3 &a, const meow::circle &b);
	convexHull operator*(const meow::mat3 &a, const meow::convexHull &b);
	plane operator*(const meow::mat3 &a, const meow::plane &b);
	ray operator*(const meow::mat3 &a, const meow::ray &b);
}


#endif