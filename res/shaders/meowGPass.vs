// shadertype=glsl


#version 430

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec4 normal;
layout(location = 3) in vec2 texCoord;

out vec4 vPos;
out vec4 vNorm;
out vec2 vUV;

layout(location = 0) uniform mat4 model;
layout(location = 1) uniform mat4 view;
layout(location = 2) uniform mat4 proj;
layout(location = 3) uniform float opacity;

layout(location = 4) uniform sampler2D diffM;
layout(location = 5) uniform sampler2D normalM;
layout(location = 6) uniform sampler2D specM;
layout(location = 7) uniform sampler2D glowM;
layout(location = 8) uniform sampler2D vertHM;


void main()
{
	vUV = texCoord;
	vec4 posit = position + normal * (texture(vertHM, vUV) * 2.0f - 1.0f).g;
	vPos = view * model * posit;
	vNorm = view * model * normal;


	gl_Position = proj * vPos;
}