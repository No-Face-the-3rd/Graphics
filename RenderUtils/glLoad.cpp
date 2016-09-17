#include "glLoad.h"
#include "glMake.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tinyobj\tiny_obj_loader.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb\stb_image.h>

#include "glinclude.h"
#include "Vertex.h"



Geometry loadOBJ(const char * path)
{
	glLog("loading OBJ", path);

	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string err;

	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path);

	int vSize = shapes[0].mesh.indices.size();

	vertex *verts = new vertex[vSize];
	unsigned *tris = new unsigned[vSize];

	for (int i = 0; i < vSize; i++)
	{
		auto ind = shapes[0].mesh.indices[i];

		const float *p = &attrib.vertices[ind.vertex_index * 3];
		const float *n = &attrib.normals[ind.normal_index * 3];


		verts[i].position = glm::vec4(p[0], p[1], p[2], 1.0f);
		verts[i].normal = glm::vec4(n[0], n[1], n[2], 0.0f);
		if (ind.texcoord_index >= 0)
		{
			const float *t = &attrib.texcoords[ind.texcoord_index * 2];
			verts[i].texCoord = glm::vec2(t[0], t[1]);
		}


		tris[i] = i;
	}




	Geometry retVal = makeGeometry(verts, vSize, tris, vSize);

	delete[] verts;
	delete[] tris;

	return retVal;
}

Shader loadShader(const char * vShaderFile, const char * fShaderFile)
{
	std::string vCode, fCode;
	std::ifstream vertShaderFile(vShaderFile);
	std::ifstream fragShaderFile(fShaderFile);
	std::stringstream vShaderStream, fShaderStream;

	vShaderStream << vertShaderFile.rdbuf();
	fShaderStream << fragShaderFile.rdbuf();

	vertShaderFile.close();
	fragShaderFile.close();

	vCode = vShaderStream.str();
	fCode = fShaderStream.str();

	const char *vertCode = vCode.c_str(), *fragCode = fCode.c_str();

	return makeShader(vertCode, fragCode);
}




Texture loadTexture(const char * path)
{
	glLog("Loading Texture", path);

	Texture ret = { 0,0,0,0 };
	int width, height, format;
	unsigned char *pixels;

	stbi_set_flip_vertically_on_load(true);
	pixels = stbi_load(path, &width, &height, &format, STBI_default);

	if (!pixels)
	{
		return ret;
	}

	switch (format)
	{
	case STBI_grey:
		format = GL_RED;
		break;
	case STBI_grey_alpha:
		format = GL_RG;
		break;
	case STBI_rgb:
		format = GL_RGB;
		break;
	case STBI_rgb_alpha:
		format = GL_RGBA;
		break;
	}

	ret = makeTexture(width, height, format, pixels);
	stbi_image_free(pixels);

	return ret;
}