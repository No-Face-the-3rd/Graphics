#pragma once



#ifndef GL_LOAD_MEOW_H
#define GL_LOAD_MEOW_H

#include "globjects.h"



Geometry loadOBJ(const char *path);


Shader loadShader(const char *vShaderFile, const char *fShaderFile);

Texture loadTexture(const char *path);



#endif
