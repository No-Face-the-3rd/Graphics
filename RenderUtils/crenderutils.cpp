#include "Decs.h"

#include "crenderutils.h"
#include "Vertex.h"

#define TINYOBJLOADER_IMPLEMENTATION

#include "tinyobj\tiny_obj_loader.h"

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include "glm\gtc\random.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb\stb_image.h>

#define NULL 0

Geometry makeGeometry(const vertex * verts, size_t v_size, const unsigned int * tris, size_t t_size)
{
	Geometry retVal;
	retVal.size = t_size;

	//Define the variables
	glGenBuffers(1, &retVal.vbo); //store vertices
	glGenBuffers(1, &retVal.ibo); //store indices
	glGenVertexArrays(1, &retVal.vao); //store attribute info

	//Scope the variables
	glBindVertexArray(retVal.vao);
	glBindBuffer(GL_ARRAY_BUFFER, retVal.vbo); //scope vertices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, retVal.ibo); //scope triangle

	//Initialize the variables
	glBufferData(GL_ARRAY_BUFFER, v_size * sizeof(vertex), verts, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, t_size * sizeof(unsigned), tris, GL_STATIC_DRAW);

	//Attributes
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	//attribute index, num elements, type, normalize?,size of vertex, offset
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)vertex::POSITION);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)vertex::COLOR);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)vertex::NORMAL);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)vertex::TEXCOORD);

	//unscope the variables
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	return retVal;
}

void freeGeometry(Geometry & geo)
{
	glDeleteBuffers(1, &geo.vbo);
	glDeleteBuffers(1, &geo.ibo);
	glDeleteVertexArrays(1, &geo.vao);
	geo = { 0,0,0,0 };
}

Geometry loadOBJ(const char * path)
{
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


		verts[i].position = glm::vec4(p[0], p[1],p[2],1.0f);
		verts[i].normal = glm::vec4(n[0], n[1], n[2], 0.0f);
		if (ind.texcoord_index >= 0)
		{
			const float *t = &attrib.texcoords[ind.texcoord_index * 2];
			verts[i].texCoord = glm::vec2(t[0], t[1]);
		}
		else
		{
			verts[i].texCoord = glm::vec2(glm::linearRand(0.0f, 1.0f), glm::linearRand(0.0f, 1.0f));
		}

		tris[i] = i;
	}

	

	
	Geometry retVal = makeGeometry(verts, vSize,tris, vSize );

	delete[] verts;
	delete[] tris;

	return retVal;
}

Shader makeShader(const char * vsource, const char * fsource)
{
	Shader retVal;

	//create variables
	retVal.handle = glCreateProgram();
	unsigned vs = glCreateShader(GL_VERTEX_SHADER);
	unsigned fs = glCreateShader(GL_FRAGMENT_SHADER);

	//initialize variables
	glShaderSource(vs, 1, &vsource, NULL);
	glShaderSource(fs, 1, &fsource, NULL);

	//compile shaders
	glCompileShader(vs);
	glCompileShader(fs);

	//link shaders
	glAttachShader(retVal.handle, vs);
	glAttachShader(retVal.handle, fs);
	glLinkProgram(retVal.handle);

	//delete shaders after no longer necessary
	glDeleteShader(vs);
	glDeleteShader(vs);

	return retVal;
}

Shader loadShader(const char * vpath, const char * fpath)
{

	return loadShaderFromFile(vpath,fpath);
}

Shader loadShaderFromFile(const char * vShaderFile, const char * fShaderFile)
{
	std::string vCode, fCode;
	try
	{
		std::ifstream vertShaderFile(vShaderFile);
		std::ifstream fragShaderFile(fShaderFile);
		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vertShaderFile.rdbuf();
		fShaderStream << fragShaderFile.rdbuf();

		vertShaderFile.close();
		fragShaderFile.close();

		vCode = vShaderStream.str();
		fCode = fShaderStream.str();
	}
	catch (std::exception e)
	{
		std::cout << "Shaders failed to read!\n";
	}
	const char *vertCode = vCode.c_str(), *fragCode = fCode.c_str();

	return makeShader(vertCode, fragCode);
}

void freeShader(Shader & shader)
{
	glDeleteProgram(shader.handle);
	shader.handle = 0;
}

void draw(const Shader & shader, const Geometry & geo)
{
	glUseProgram(shader.handle);
	glBindVertexArray(geo.vao);

	glDrawElements(GL_TRIANGLES, geo.size, GL_UNSIGNED_INT, 0);
}

void draw(const Shader & shader, const Geometry & geo, float time)
{

	glUseProgram(shader.handle);
	glBindVertexArray(geo.vao);

	glUniform1f(glGetUniformLocation(shader.handle, "time"), time);

	glDrawElements(GL_TRIANGLES, geo.size, GL_UNSIGNED_INT, 0);
}

void draw(const Shader & shader, const Geometry & geo, const float M[16], const float V[16], const float P[16])
{
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glUseProgram(shader.handle);
	glBindVertexArray(geo.vao);

	glUniformMatrix4fv(0, 1, GL_FALSE, P);
	glUniformMatrix4fv(1, 1, GL_FALSE, V);
	glUniformMatrix4fv(2, 1, GL_FALSE, M);




	glDrawElements(GL_TRIANGLES, geo.size, GL_UNSIGNED_INT, 0);

}

Texture makeTexture(unsigned width, unsigned height, unsigned format, const unsigned char * pixels)
{
	Texture ret = { 0, width, height, format };

	glGenTextures(1, &ret.handle);
	glBindTexture(GL_TEXTURE_2D, ret.handle);

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);

	return ret;
}

Texture makeTextureF(unsigned square, const float * pixels)
{
	Texture ret = { 0,square, square, GL_RED };

	glGenTextures(1, &ret.handle);
	glBindTexture(GL_TEXTURE_2D, ret.handle);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, square, square, 0, GL_RED, GL_FLOAT, pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_2D, 0);


	return ret;
}

Texture loadTexture(const char * path)
{
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

void freeTexture(Texture & tex)
{
	glDeleteTextures(1, &tex.handle);
	tex = { 0,0,0,0 };
}

void draw(const Shader & shader, const Geometry & geo, const Texture & tex, const float M[16], const float V[16], const float P[16], float time)
{
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glUseProgram(shader.handle);
	glBindVertexArray(geo.vao);

	glUniformMatrix4fv(0, 1, GL_FALSE, P);
	glUniformMatrix4fv(1, 1, GL_FALSE, V);
	glUniformMatrix4fv(2, 1, GL_FALSE, M);

	glUniform1f(3, time);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex.handle);
	glUniform1i(4, 0);

	glDrawElements(GL_TRIANGLES, geo.size, GL_UNSIGNED_INT, 0); 
}

void draw(const Shader & shader, const Geometry & geo, const float M[16], const float V[16], const float P[16], const Texture * tex, unsigned t_count, float time)
{
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);


	glUseProgram(shader.handle);
	glBindVertexArray(geo.vao);

	glUniformMatrix4fv(0, 1, GL_FALSE, P);
	glUniformMatrix4fv(1, 1, GL_FALSE, V);
	glUniformMatrix4fv(2, 1, GL_FALSE, M);

	glUniform1f(3, time);

	for (int i = 0; i < t_count; ++i)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, tex[i].handle);
		glUniform1i(12 + i, 0 + i);
	}

	glDrawElements(GL_TRIANGLES, geo.size, GL_UNSIGNED_INT, 0);
}


Geometry generatePlane(unsigned rows, unsigned cols)
{
	Geometry ret;

	unsigned vSize = rows * cols, tSize = (rows - 1) * (cols - 1) * 6;

	vertex *verts = new vertex[vSize];
	unsigned *tris = new unsigned[tSize];

	unsigned ind = 0;

	for (unsigned i = 0; i < rows; ++i)
	{
		for (unsigned j = 0; j < cols; ++j)
		{
			verts[i * cols + j].position[0] = (float)j;
			verts[i * cols + j].position[1] = 0.0f;
			verts[i * cols + j].position[2] = (float)i;
			verts[i * cols + j].position[3] = 1.0f;
			verts[i * cols + j].color[0] = verts[i * cols + j].color[1] = verts[i * cols + j].color[2] = verts[i * cols + j].color[3] = 1.0f;
			
			if (i < rows - 1 && j < cols - 1)
			{
				tris[ind++] = i * cols + j;
				tris[ind++] = (i + 1) * cols + j;
				tris[ind++] = (i + 1) * cols + (j + 1);

				tris[ind++] = i * cols + j;
				tris[ind++] = (i + 1) * cols + (j + 1);
				tris[ind++] = i * cols + (j + 1);
			}

			verts[i * cols + j].texCoord[0] = verts[i * cols + j].position[0] / (cols - 1);
			verts[i * cols + j].texCoord[1] = verts[i * cols + j].position[2] / (rows - 1);

			verts[i * cols + j].normal = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);

		}
	}

	ret = makeGeometry(verts, vSize, tris, tSize);

	delete[] verts;
	delete[] tris;

	return ret;
}

frameBuffer makeFrameBuffer(unsigned width, unsigned height, unsigned numColors)
{
	frameBuffer ret = { 0,width,height,0,0,0,0,0,0,0,0 };

	glGenFramebuffers(1, &ret.handle);
	glBindFramebuffer(GL_FRAMEBUFFER, ret.handle);

	const GLenum attachments[8] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3, GL_COLOR_ATTACHMENT4, GL_COLOR_ATTACHMENT5, GL_COLOR_ATTACHMENT6, GL_COLOR_ATTACHMENT7 };

	for (int i = 0; i < numColors && i < 8; i++)
	{
		ret.colors[i] = makeTexture(width, height, GL_RGBA, 0);
		glFramebufferTexture(GL_FRAMEBUFFER, attachments[i], ret.colors[i].handle, 0);
	}

	glDrawBuffers(numColors, attachments);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return ret;
}

void freeFrameBuffer(frameBuffer & buff)
{
}
