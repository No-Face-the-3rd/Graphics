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

const vertex quadVerts[4] = { { { -1,-1,0,1 },{ 0,0,0,1 },{ 0,0,1,0 },{ 0,0 } },{ { 1,-1,0,1 },{ 0,0,1,1 },{ 0,0,1,0 },{ 1,0 } },{ { 1,1,0,1 },{ 0,1,0,1 },{ 0,0,1,0 },{ 1,1 } },{ { -1,1,0,1 },{ 1,0,0,1 },{ 0,0,1,0 },{ 0,1 } } };
const unsigned quadTris[6] = { 0,1,2,2,3,0 };



#endif

