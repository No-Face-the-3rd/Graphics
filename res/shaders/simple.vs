#version 430

layout(location = 0)in vec4 position;
layout(location = 1)in vec4 color;

out vec4 vColor;
out vec4 vPos;

layout(location = 0) uniform float time;

void main()
{
	gl_Position = position;
	vColor = color;

}