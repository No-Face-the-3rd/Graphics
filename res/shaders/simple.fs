#version 430

out vec4 outColor;
in vec4 vColor;

layout(location = 0)uniform float time;

void main()
{
	outColor = vColor;

}