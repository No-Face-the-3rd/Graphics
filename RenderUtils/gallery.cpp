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

//bool gallery::generatePlane(const char * name, unsigned rows, unsigned cols)
//{
//	if (geometries.find(name) != geometries.end())
//		return false;
//	else
//		geometries[name] = ::generatePlane(rows, cols);
//	return true;
//}

bool gallery::loadObjectOBJ(const char * name, const char * path)
{
	if (geometries.find(name) != geometries.end())
		return false;
	else
		geometries[name] = ::loadOBJ(path);
	return true;
}

bool gallery::makeTexture(const char * name, unsigned width, unsigned height, unsigned format, const unsigned char * pixels)
{
	if (textures.find(name) != textures.end())
		return false;
	else
		textures[name] = ::makeTexture(width, height, format, pixels);

	return true;
}

bool gallery::loadTexture(const char * name, const char * path)
{
	if (textures.find(name) != textures.end())
		return false;
	else
		textures[name] = ::loadTexture(path);
	return true;
}

const Geometry & gallery::getGeometry(const char * name)
{
	return geometries.at(name);
}

const Shader & gallery::getShader(const char * name)
{
	return shaders.at(name);
}

const Texture & gallery::getTexture(const char * name)
{
	return textures.at(name);
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
	for each(auto texture in textures)
	{
		freeTexture(texture.second);
	}

	return true;
}
