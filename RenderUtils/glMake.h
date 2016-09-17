#pragma once



#ifndef GL_MAKE_MEOW_H
#define GL_MAKE_MEOW_H

#include "globjects.h"

Geometry makeGeometry(const struct vertex *verts, size_t v_size, const unsigned int *tris, size_t tsize);

void freeGeometry(Geometry &geo);


Shader makeShader(const char *vsource, const char *fsource);

void freeShader(Shader &shader);


Texture makeTexture(unsigned width, unsigned height, unsigned format, const unsigned char *pixels);

Texture makeTextureF(unsigned square, const float *pixels);

void freeTexture(Texture &tex);


frameBuffer makeFrameBuffer(unsigned width, unsigned height, unsigned numColors);

void freeFrameBuffer(frameBuffer &buff);



#endif
