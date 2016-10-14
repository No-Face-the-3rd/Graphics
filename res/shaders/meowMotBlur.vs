// shadertype=glsl

#version 430

layout(location = 0) in vec4 position;
layout(location = 3) in vec2 texCoord;

layout(location = 0) uniform sampler2D prevFrame;
layout(location = 1) uniform sampler2D curFrame;
layout(location = 2) uniform float ratio;

out vec2 vUV;

void main()
{
	vUV = texCoord;
	gl_Position = position;
}
