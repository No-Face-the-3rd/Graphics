// shadertype=glsl

#version 430

layout(location = 0) in vec4 position;
layout(location = 3) in vec2 texCoord;

out vec2 vUV;

layout(location = 0) uniform sampler2D diffM;

void main()
{
	vUV = texCoord;
	gl_Position = position;
}