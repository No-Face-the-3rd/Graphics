#pragma once

#ifndef VERTEX_H
#define VERTEX_H

#include "glm\glm.hpp"

struct vertex
{
	glm::vec4 position;
	glm::vec4 color;
	glm::vec4 normal;
	glm::vec2 texCoord;

	enum {
		POSITION = 0,
		COLOR =  16,
		NORMAL = 32,
		TEXCOORD = 48
	};
};



#endif

