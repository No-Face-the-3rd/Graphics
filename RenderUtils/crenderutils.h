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

Geometry makeGeometry(const struct vertex *verts, size_t v_size, const unsigned int *tris, size_t tsize);

void freeGeometry(Geometry &geo);

Geometry loadOBJ(const char *path);

struct Shader
{
	unsigned handle;
};

Shader makeShader(const char *vsource, const char *fsource);

Shader loadShader(const char *vpath, const char *fpath);

Shader loadShaderFromFile(const char *vShaderFile, const char *fShaderFile);

void freeShader(Shader &shader);

void draw(const Shader &shader, const Geometry &geo);

void draw(const Shader &shader, const Geometry &geo, float time);

void draw(const Shader &shader, const Geometry &geo, const float M[16], const float V[16], const float P[16]);

#endif