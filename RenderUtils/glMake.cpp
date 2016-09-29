#include "glinclude.h"
#include "glMake.h"
#include "Vertex.h"


Geometry makeGeometry(const struct vertex *verts, size_t v_size, const unsigned int *tris, size_t tsize)
{

	Geometry retVal;
	retVal.size = tsize;

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
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, tsize * sizeof(unsigned), tris, GL_STATIC_DRAW);

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

void freeGeometry(Geometry &geo)
{
	glDeleteBuffers(1, &geo.vbo);
	glDeleteBuffers(1, &geo.ibo);
	glDeleteVertexArrays(1, &geo.vao);
	geo = { 0,0,0,0 };
}


Shader makeShader(const char *vsource, const char *fsource, bool depth, bool add, bool face)
{
	Shader retVal = { 0, depth, add, face };

	//create variables
	retVal.handle = glCreateProgram();
	unsigned vs = glCreateShader(GL_VERTEX_SHADER);
	unsigned fs = glCreateShader(GL_FRAGMENT_SHADER);

	//initialize variables
	glShaderSource(vs, 1, &vsource, NULL);
	glShaderSource(fs, 1, &fsource, NULL);

	//compile shaders
	glLog_glCompileShader(vs);
	glLog_glCompileShader(fs);

	//link shaders
	glAttachShader(retVal.handle, vs);
	glAttachShader(retVal.handle, fs);
	glLog_glLinkProgram(retVal.handle);

	//delete shaders after no longer necessary
	glDeleteShader(vs);
	glDeleteShader(vs);

	return retVal;
}

void freeShader(Shader &shader)
{
	glDeleteProgram(shader.handle);
	shader.handle = 0;
}


Texture makeTexture(unsigned width, unsigned height, unsigned channels, const void *pixels, bool isFloat)
{
	glLog("TODO", "Parameter for Channel Count + bit depth + type");
	GLenum externFormat = GL_RGBA;
	GLenum internFormat = isFloat ? GL_RGBA32F : externFormat;

	switch (channels)
	{
	case 0:
		externFormat = GL_DEPTH_COMPONENT;
		internFormat = GL_DEPTH24_STENCIL8;
		break;
	case 1: 
		externFormat = GL_RED;
		internFormat = isFloat ? GL_R32F : externFormat;
		break;
	case 2:
		externFormat = GL_RG;
		internFormat = isFloat ? GL_RG32F : externFormat;
		break;
	case 3:
		externFormat = GL_RGB;
		internFormat = isFloat ? GL_RGB32F : externFormat;
		break;
	case 4:
		externFormat = GL_RGBA;
		internFormat = isFloat ? GL_RGBA32F : externFormat;
		break;
	default:
		glLog("ERROR", "Channels must be 0-4");

	}

	Texture ret = { 0, width, height, channels };

	glGenTextures(1, &ret.handle);
	glBindTexture(GL_TEXTURE_2D, ret.handle);

	glTexImage2D(GL_TEXTURE_2D, 0, internFormat, width, height, 0, externFormat, isFloat ? GL_FLOAT : GL_UNSIGNED_BYTE, pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);

	return ret;
}

Texture makeTextureF(unsigned square, const float *pixels)
{
	glLog("TODO", "Deprecate");
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

void freeTexture(Texture &tex)
{
	glDeleteTextures(1, &tex.handle);
	tex = { 0,0,0,0 };
}


frameBuffer makeFrameBuffer(unsigned width, unsigned height, unsigned numColors, const bool *isFloat, const int *channels)
{
	glLog("TODO", "State management + better depth buffer + options");

	frameBuffer ret = { 0,width,height,numColors };

	glGenFramebuffers(1, &ret.handle);
	glBindFramebuffer(GL_FRAMEBUFFER, ret.handle);

	ret.depth = makeTexture(width, height, 0, 0);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, ret.depth.handle, 0);

	const GLenum attachments[8] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3, GL_COLOR_ATTACHMENT4, GL_COLOR_ATTACHMENT5, GL_COLOR_ATTACHMENT6, GL_COLOR_ATTACHMENT7 };

	for (int i = 0; i < numColors && i < 8; i++)
	{
		ret.colors[i] = makeTexture(width, height, channels && channels[i] != 0 ? channels[i] : 4, 0, isFloat ? isFloat[i] : false);
		glFramebufferTexture(GL_FRAMEBUFFER, attachments[i], ret.colors[i].handle, 0);
	}

	glDrawBuffers(numColors, attachments);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return ret;
}

void freeFrameBuffer(frameBuffer &buff)
{
	for (unsigned i = 0; i < buff.numColors; i++)
	{
		freeTexture(buff.colors[i]);
	}

	glDeleteFramebuffers(1, &buff.handle);
	buff = { 0,0,0,0 };

}