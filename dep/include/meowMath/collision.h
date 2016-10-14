#pragma once

#ifndef COLLISION_H
#define COLLISION_H

#include "shapes.h"
#include "mat4.h"

namespace meow
{
	struct collisionData
	{
		bool collided;
		float depth;
		meow::vec2 normal;
		collisionData(bool a = false, float b = 0.0f, meow::vec2 c = { 0.0f,0.0f }) : collided(a), depth(b), normal(c){}
	};

	float pointPlaneDist(const meow::vec2 &a, const meow::plane &b);
	float rayPlaneDist(const meow::ray &a, const meow::plane &b);

	collisionData cTest(const meow::aabb &a, const meow::aabb &b);
	collisionData cTest(const meow::aabb &a, const meow::circle &b);
	collisionData cTest(const meow::aabb &a, const meow::convexHull &b);
	collisionData cTest(const meow::aabb &a, const meow::plane &b);
	collisionData cTest(const meow::aabb &a, const meow::ray &b);
	collisionData cTest(const meow::circle &a, const meow::aabb &b);
	collisionData cTest(const meow::circle &a, const meow::circle &b);
	collisionData cTest(const meow::circle &a, const meow::convexHull &b);
	collisionData cTest(const meow::circle &a, const meow::plane &b);
	collisionData cTest(const meow::circle &a, const meow::ray &b);
	collisionData cTest(const meow::convexHull &a, const meow::aabb &b);
	collisionData cTest(const meow::convexHull &a, const meow::circle &b);
	collisionData cTest(const meow::convexHull &a, const meow::convexHull &b);
	collisionData cTest(const meow::convexHull &a, const meow::plane &b);
	collisionData cTest(const meow::convexHull &a, const meow::ray &b);
	collisionData cTest(const meow::plane &a, const meow::aabb &b);
	collisionData cTest(const meow::plane &a, const meow::circle &b);
	collisionData cTest(const meow::plane &a, const meow::convexHull &b);
	collisionData cTest(const meow::plane &a, const meow::plane &b);
	collisionData cTest(const meow::plane &a, const meow::ray &b);
	collisionData cTest(const meow::ray &a, const meow::aabb &b);
	collisionData cTest(const meow::ray &a, const meow::circle &b);
	collisionData cTest(const meow::ray &a, const meow::convexHull &b);
	collisionData cTest(const meow::ray &a, const meow::plane &b);
	collisionData cTest(const meow::ray &a, const meow::ray &b);

}





#endif