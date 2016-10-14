// shadertype=glsl

#version 430

layout(location = 0) in vec4 position;
layout(location = 3) in vec2 texCoord;

layout(location = 0) uniform mat4 model;
layout(location = 1) uniform mat4 view;
layout(location = 2) uniform mat4 proj;
layout(location = 3) uniform float time;

layout(location = 4) uniform sampler2D albedoM;
layout(location = 5) uniform sampler2D normalM;
layout(location = 6) uniform sampler2D specM;
layout(location = 7) uniform sampler2D positionM;
layout(location = 8) uniform sampler2D shadowM;

layout(location = 9) uniform vec4 lCol;
layout(location = 10) uniform mat4 lView;
layout(location = 11) uniform mat4 lProj;

out vec2 UV;

void main()
{

	UV = texCoord;
	gl_Position = position;

}

