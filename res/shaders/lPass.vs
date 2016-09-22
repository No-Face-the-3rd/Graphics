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
layout(location = 8) uniform sampler2D depthM;

layout(location = 9) uniform vec4 lDir = normalize(vec4(-1,-1,-1,0));

out vec2 UV;

void main()
{

	UV = texCoord;
	gl_Position = position;

}

