#pragma once



#ifndef GL_INCLUDE_MEOW_H
#define GL_INCLUDE_MEOW_H

#define GLEW_STATIC
#include "GLEW\glew.h"
#include "GLFW\glfw3.h"


#ifdef _DEBUG

#include <iostream>

#define glLog(details, extra)\
do\
{\
std::cout << "In " << __FILE__ << " at " << __FUNCTION__ << " on line " << __LINE__ <<  ": " << details << ", " << extra << std::endl;\
}while(0)

#define glLog_glCompileShader(shader)\
do\
{\
glCompileShader(shader);\
GLint success = GL_FALSE;\
glGetShaderiv(shader,GL_COMPILE_STATUS, &success);\
if(success == GL_FALSE)\
{\
int length = 0;\
glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);\
char *log = (char*)malloc(length);\
glGetShaderInfoLog(shader, length, NULL, log);\
std::cout << log << std::endl;\
free(log);\
}\
}while(0)


#define glLog_glLinkProgram(shader)\
do\
{\
glLinkProgram(shader);\
GLint success = GL_FALSE;\
glGetProgramiv(shader,GL_LINK_STATUS, &success);\
if(success == GL_FALSE)\
{\
int length = 0;\
glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &length);\
char *log = (char*)malloc(length);\
glGetProgramInfoLog(shader, length, NULL, log);\
std::cout << log << std::endl;\
free(log);\
}\
}while(0)

#else
#define glLog(details, extra)
#define glLog_glCompileShader(shader) glCompileShader(shader)
#define glLog_glLinkProgram(shader) glLinkProgram(shader)

#endif



#endif
