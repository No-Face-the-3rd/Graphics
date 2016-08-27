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

	bool makeShader(const char *name, const char *vSource, const char *fSource);
	bool loadShader(const char *name, const char *vPath, const char *fPath);

	bool makeGeometry(const char *name, const vertex *verts, size_t vSize, const unsigned *tris, size_t tSize);

	bool loadObjectOBJ(const char *name, const char *path);

	const Geometry &getGeometry(const char *name);
	const Shader &getShader(const char *name);

	bool init();
	bool term();

};





#endif

