#pragma once



#ifndef GL_DRAW_MEOW_H
#define GL_DRAW_MEOW_H

#include <glm\fwd.hpp>
#include "globjects.h"
#include <cstring>

void clearFrameBuffer(const frameBuffer &buff);

namespace tDraw_internal
{
	void tDraw_begin(const Shader &shader, const Geometry &geo, const frameBuffer &buff);
	void tDraw_close(const Shader &shader, const Geometry &geo, const frameBuffer &buff);

	size_t tDraw_format(size_t idx, size_t texInd, float val);
	size_t tDraw_format(size_t idx, size_t texInd, int val);
	size_t tDraw_format(size_t idx, size_t texInd, const Texture &val);
	size_t tDraw_format(size_t idx, size_t texInd, const glm::mat3 &val);
	size_t tDraw_format(size_t idx, size_t texInd, const glm::mat4 &val);
	size_t tDraw_format(size_t idx, size_t texInd, const glm::vec3 &val);
	size_t tDraw_format(size_t idx, size_t texInd, const glm::vec4 &val);



	template< typename T, typename ...U>
	void tDraw_unpack(size_t idx, size_t texInd, T val, U &&...uniforms)
	{
		texInd += tDraw_format(idx, texInd, val);
		tDraw_unpack(idx + 1, texInd + 1, uniforms...);
	}

	template<typename T>
	void tDraw_unpack(size_t idx, size_t texInd, T val)
	{
		tDraw_format(idx, texInd, val);
	}
}

template<typename ...U>
void tDraw(const Shader &shader, const Geometry &geo, const frameBuffer &buff, U ... uniforms)
{
	tDraw_internal::tDraw_begin(shader, geo, buff);

	tDraw_internal::tDraw_unpack(0, 0, uniforms...);

	tDraw_internal::tDraw_close(shader, geo, buff);
}


inline void tDraw(const Shader &shader, const Geometry &geo, const frameBuffer &buff)
{
	tDraw_internal::tDraw_begin(shader, geo, buff);
	tDraw_internal::tDraw_close(shader, geo, buff);
}



#endif
