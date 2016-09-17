#pragma once

#ifndef GL_OBJECTS_MEOW_H
#define GL_OBJECTS_MEOW_H

struct Geometry
{
	// VAO : Vertex Array Object : Groups the two with some formatting
	unsigned vao;
	// VBO : Vertex Buffer Object : an array of vertices
	unsigned vbo;
	// IBO : Index Buffer Object : an array of indices(triangles)
	unsigned ibo;
	// size : number of triangles
	unsigned size;
};

struct Shader
{
	unsigned handle;
};


struct Texture
{
	unsigned handle;
	unsigned width, height, format;
};

struct frameBuffer
{
	unsigned handle;
	
	unsigned width, height, numColors;
	
	Texture depth;
	Texture colors[8];
};


#endif
