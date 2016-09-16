#pragma once

struct Geometry
{
	// VBO : Vertex Buffer Object : an array of vertices
	// IBO : Index Buffer Object : an array of indices(triangles)
	// VAO : Vertex Array Object : Groups the two with some formatting
	// size : number of triangles
	unsigned vao, vbo, ibo, size;
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