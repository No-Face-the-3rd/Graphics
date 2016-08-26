#include "Decs.h"

#include "crenderutils.h"
#include "Vertex.h"

#define NULL 0

Geometry makeGeometry(const Vertex * verts, size_t v_size, const unsigned int * tris, size_t t_size)
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
	glBufferData(GL_ARRAY_BUFFER, v_size * sizeof(Vertex), verts, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, t_size * sizeof(unsigned), tris, GL_STATIC_DRAW);

	//Attributes
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	//attribute index, num elements, type, normalize?,size of vertex, offset
	glVertexAttribPointer(0,4, GL_FLOAT,GL_FALSE,sizeof(Vertex),(void *)Vertex::POSITION);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::COLOR);

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
