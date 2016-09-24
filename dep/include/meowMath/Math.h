#pragma once

#include "collision.h"

namespace meow
{
	inline vec2 hermite(const vec2 &a, const vec2 &b, const vec2 &c, const vec2 &d, const float &e)
	{
		float f, g, h, i;
		f = std::pow(2 * e, 3) - std::pow(3 * e, 2) + 1;
		g = std::pow(-2 * e, 3) + std::pow(3 * e, 2);
		h = std::pow(e, 3) - 2 * std::pow(e, 2) + e;
		i = std::pow(e, 3) - std::pow(e, 2);

		return{ f * a.x + g * b.x + h * c.x + i * d.x,f * a.y + g * b.y + h * c.y + i * d.y };
	}

	inline vec2 bezier(const vec2 &a, const vec2 &b, const vec2 &c, const vec2 &d, const float &e)
	{
		vec2 f, g, h;
		f = lerp(a, b, e);
		g = lerp(b, c, e);
		h = lerp(c, d, e);

		return lerp(lerp(f, g, e), lerp(g, h, e), e);
	}
}