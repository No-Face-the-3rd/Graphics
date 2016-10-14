

#version 430

layout(location = 0) in vec4 position;

layout(location = 0) uniform mat4 model;
layout(location = 1) uniform mat4 view;
layout(location = 2) uniform mat4 proj;
layout(location = 3) uniform float time = 0.0f;
layout(location = 4) uniform float wave = 0.00000f;

void main()
{
	vec4 posit = view * model * position;
	posit.x += sin(time + posit.y * wave);
	gl_Position = proj * posit;
}