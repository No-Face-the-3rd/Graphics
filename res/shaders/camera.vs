#version 430

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

out vec4 vColor;
out vec4 vPosition;

layout(location = 0) uniform mat4 projection;
layout(location = 1) uniform mat4 view;
layout(location = 2) uniform mat4 model;

void main()
{

	vColor = color;
	vPosition = model * position;

	gl_Position = projection * view * model * position;
}