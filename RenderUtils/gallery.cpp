#include "gallery.h"

bool gallery::makeShader(const char * name, const char * vSource, const char * fSource)
{
	if (shaders.find(name) != shaders.end())
	{
		return false;
	}
	else
		shaders[name] = ::makeShader(vSource, fSource);
	return true;
}

bool gallery::loadShader(const char * name, const char * vPath, const char * fPath)
{
	if (shaders.find(name) != shaders.end())
	{
		return false;
	}
	else
		shaders[name] = ::loadShader(vPath, fPath);
	return true;
}

bool gallery::makeGeometry(const char * name, const vertex * verts, size_t vSize, const unsigned * tris, size_t tSize)
{
	if (geometries.find(name) != geometries.end())
		return false;
	else
		geometries[name] = ::makeGeometry(verts, vSize, tris, tSize);
	return true;
}

bool gallery::loadObjectOBJ(const char * name, const char * path)
{
	if (geometries.find(name) != geometries.end())
		return false;
	else
		geometries[name] = ::loadOBJ(path);
	return true;
}

const Geometry & gallery::getGeometry(const char * name)
{
	return geometries[name];
}

const Shader & gallery::getShader(const char * name)
{
	return shaders[name];
}

bool gallery::init()
{
	return true;
}

bool gallery::term()
{
	for each(auto shader in shaders)
	{
		freeShader(shader.second);
	}
	for each(auto geometry in geometries)
	{
		freeGeometry(geometry.second);
	}

	return true;
}
