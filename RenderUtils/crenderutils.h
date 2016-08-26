#pragma once

#ifndef CRENDERUTILS_H
#define CRENDERUTILS_H

#include <string>

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

Shader loadShader(const char *vpath, const char *fpath);

Shader loadShaderFromFile(const char *vShaderFile, const char *fShaderFile);

void freeShader(Shader &shader);

void draw(const Shader &shader, const Geometry &geo);

#endif