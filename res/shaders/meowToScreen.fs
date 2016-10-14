// shadertype=glsl


#version 430

in vec2 vUV;

out vec4 outColor;

layout(location = 0) uniform sampler2D diffM;

void main()
{
	
	outColor = texture(diffM, vUV);
}