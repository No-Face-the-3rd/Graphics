#version 430

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 texCoord;

out vec4 vColor;
out vec4 vPosition;
out vec2 vTexCoord;

layout(location = 0) uniform mat4 projection;
layout(location = 1) uniform mat4 view;
layout(location = 2) uniform mat4 model;
layout(location = 3) uniform float time = 0.0f;

layout(location = 4) uniform sampler2D tex;
void main()
{

	vColor = color;
	vPosition = position;
	vTexCoord = texCoord;

	gl_Position = projection * view * model * position;
	gl_Position.y += texture(tex,texCoord).r * 15 + cos(time * texture(tex,texCoord).r) * 2.0f;
}