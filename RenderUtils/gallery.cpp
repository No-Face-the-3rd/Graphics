#include "gallery.h"

bool gallery::makeShader(const char * name, const char * vSource, const char * fSource, bool depth, bool add, bool face)
{
	if (shaders.find(name) != shaders.end())
	{
		return false;
	}
	else
		shaders[name] = ::makeShader(vSource, fSource, depth, add, face);
	return true;
}

bool gallery::loadShader(const char * name, const char * vPath, const char * fPath, bool depth, bool add, bool face)
{
	if (shaders.find(name) != shaders.end())
	{
		return false;
	}
	else
		shaders[name] = ::loadShader(vPath, fPath, depth, add, face);
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

bool gallery::makeTexture(const char * name, unsigned width, unsigned height, unsigned channels, const void * pixels, bool isFloat)
{
	if (textures.find(name) != textures.end())
		return false;
	else
		textures[name] = ::makeTexture(width, height, channels, pixels, isFloat);

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

bool gallery::makeFrameBuffer(const char * name, unsigned width, unsigned height, unsigned numColors, const bool * isFloat, const int * channels)
{
	if (frameBuffers.find(name) != frameBuffers.end())
		return false;
	else
		frameBuffers[name] = ::makeFrameBuffer(width, height, numColors, isFloat, channels);
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

const frameBuffer & gallery::getFrameBuffer(const char * name)
{
	return frameBuffers.at(name);
}

bool gallery::init()
{
	frameBuffers["screen"] = { 0,1360, 768,1 };
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
	for each(auto buffer in frameBuffers)
	{
		freeFrameBuffer(buffer.second);
	}

	return true;
}
