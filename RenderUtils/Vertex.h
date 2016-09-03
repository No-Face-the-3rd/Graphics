#pragma once

#ifndef VERTEX_H
#define VERTEX_H

struct vertex
{
	float position[4];
	float color[4];
	float texCoord[2];

	enum {
		POSITION = 0,
		COLOR =  16,
		TEXCOORD = 32
	};
};



#endif

