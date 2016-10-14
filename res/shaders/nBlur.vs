//shadertype=glsl

#version 430

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec4 normal;
layout(location = 3) in vec2 texCoord;

layout(location = 0) out vec2 UV;

layout(location = 0) uniform sampler2D blurTarg;
layout(location = 1) uniform int blurRange = 9;

void main()
{
	UV = texCoord;
	gl_Position = position;
}