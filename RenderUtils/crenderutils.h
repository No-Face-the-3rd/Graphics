#pragma once

#ifndef CRENDERUTILS_H
#define CRENDERUTILS_H

#include "globjects.h"

Geometry makeGeometry(const struct vertex *verts, size_t v_size, const unsigned int *tris, size_t tsize);

void freeGeometry(Geometry &geo);

Geometry loadOBJ(const char *path);


Shader makeShader(const char *vsource, const char *fsource);

Shader loadShader(const char *vpath, const char *fpath);

Shader loadShaderFromFile(const char *vShaderFile, const char *fShaderFile);

void freeShader(Shader &shader);

void draw(const Shader &shader, const Geometry &geo);

void draw(const Shader &shader, const Geometry &geo, float time);

void draw(const Shader &shader, const Geometry &geo, const float M[16], const float V[16], const float P[16]);

Texture makeTexture(unsigned width, unsigned height, unsigned format, const unsigned char *pixels);
Texture makeTextureF(unsigned square, const float *pixels);

Texture loadTexture(const char *path);

void freeTexture(Texture &tex);

void draw(const Shader &shader, const Geometry &geo, const Texture &tex, const float M[16], const float V[16], const float P[16], float time = 0.0f);
void draw(const Shader &shader, const Geometry &geo, const float M[16], const float V[16], const float P[16], const Texture *tex, unsigned t_count, float time = 0.0f);



Geometry generatePlane(unsigned rows, unsigned cols);

#endif