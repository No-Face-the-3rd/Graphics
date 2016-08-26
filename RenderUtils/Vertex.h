#pragma once

#ifndef VERTEX_H
#define VERTEX_H

struct Vertex
{
	float position[4];
	float color[4];

	enum{
		POSITION = 0,
		COLOR = 16
	};
};



#endif

