// shadertype=glsl

#version 430

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec4 normal;
layout(location = 3) in vec2 texCoord;

out vec4 vPosition;
out vec4 vColor;
out vec4 vNormal;
out vec2 UV;

layout(location = 0) uniform mat4 model;
layout(location = 1) uniform mat4 view;
layout(location = 2) uniform mat4 proj;
layout(location = 3) uniform float time;

layout(location = 4) uniform sampler2D diffM;
layout(location = 5) uniform sampler2D normalM;
layout(location = 6) uniform sampler2D specM;



void main()
{

	vColor = color;
	vPosition = view * model * position;
	UV = texCoord;
	vNormal = view * model * normal;


	vec4 posit = position;



	gl_Position = proj * view * model * posit;

}