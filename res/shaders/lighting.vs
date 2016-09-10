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

layout(location = 0) uniform mat4 proj;
layout(location = 1) uniform mat4 view;
layout(location = 2) uniform mat4 model;
layout(location = 3) uniform float time;


layout(location = 4) uniform vec4 lightDir;
layout(location = 5) uniform vec4 lightAmb;
layout(location = 6) uniform vec4 lightDif;
layout(location = 7) uniform vec4 lightSpec;

layout(location = 8) uniform vec4 surfAmb;
layout(location = 9) uniform vec4 surfDif;
layout(location = 10) uniform vec4 surfSpec;

layout(location = 11) uniform float specPow;

layout(location = 12) uniform sampler2D diffM;
layout(location = 13) uniform sampler2D normalM;
layout(location = 14) uniform sampler2D specM;


void main()
{

	vColor = color;
	vPosition = position;
	UV = texCoord;
	vNormal = normal;


	vec4 posit = position;



	gl_Position = proj * view * model * posit;

}