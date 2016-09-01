#include "Decs.h"

#include "crenderutils.h"
#include "Vertex.h"

#define TINYOBJLOADER_IMPLEMENTATION

#include "tinyobj\tiny_obj_loader.h"

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>


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

	//attribute index, num elements, type, normalize?,size of vertex, offset
	glVertexAttribPointer(0,4, GL_FLOAT,GL_FALSE,sizeof(vertex),(void *)vertex::POSITION);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)vertex::COLOR);

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

	vertex *verts = new vertex[attrib.vertices.size() / 3];
	unsigned *tris = new unsigned[shapes[0].mesh.indices.size()];

	for (int i = 0; i < attrib.vertices.size() / 3; ++i)
	{
		verts[i] = { attrib.vertices[i * 3],attrib.vertices[i * 3 + 1], attrib.vertices[i * 3 + 2],1 };
	}

	for (int i = 0; i < shapes[0].mesh.indices.size(); ++i)
	{
		tris[i] = shapes[0].mesh.indices[i].vertex_index;
	}
	Geometry retVal = makeGeometry(verts, attrib.vertices.size() / 3,tris, shapes[0].mesh.indices.size() );

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
