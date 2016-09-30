#pragma once


#ifndef GALLERY_H
#define GALLERY_H

#include <string>
#include <map>

#include "crenderutils.h"

class gallery
{
public:
	static gallery gal;
	std::map<std::string, Geometry> geometries;
	std::map<std::string, Shader> shaders;
	std::map<std::string, Texture> textures;
	std::map<std::string, frameBuffer> frameBuffers;

	bool makeShader(const char *name, const char *vSource, const char *fSource, bool depth = true, bool add = false, bool face = true);
	bool loadShader(const char *name, const char *vPath, const char *fPath, bool depth = true, bool add = false, bool face = true);

	bool makeGeometry(const char *name, const vertex *verts, size_t vSize, const unsigned *tris, size_t tSize);
	//bool generatePlane(const char *name, unsigned rows, unsigned cols);


	bool loadObjectOBJ(const char *name, const char *path);

	bool makeTexture(const char *name, unsigned width, unsigned height, unsigned channels, const void *pixels, bool isFloat = false);
	bool loadTexture(const char *name, const char *path);

	bool makeFrameBuffer(const char * name, unsigned width, unsigned height, unsigned numColors, const bool *isFloat = nullptr, const int *channels = nullptr);

	const Geometry &getGeometry(const char *name);
	const Shader &getShader(const char *name);
	const Texture &getTexture(const char *name);
	const frameBuffer &getFrameBuffer(const char *name);

	bool init();
	bool term();

};





#endif

