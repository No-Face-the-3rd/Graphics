#pragma once

#ifndef CRENDERUTILS_H
#define CRENDERUTILS_H



struct Geometry
{
	// VBO : Vertex Buffer Object : an array of vertices
	// IBO : Index Buffer Object : an array of indices(triangles)
	// VAO : Vertex Array Object : Groups the two with some formatting
	// size : number of triangles
	unsigned vao, vbo, ibo, size;
};

Geometry makeGeometry(const struct Vertex *verts, size_t v_size, const unsigned int *tris, size_t tsize);

void freeGeometry(Geometry &geo);

struct Shader
{
	unsigned handle;
};

Shader makeShader(const char *vsource, const char *fsource);

void freeShader(Shader &shader);


#endif