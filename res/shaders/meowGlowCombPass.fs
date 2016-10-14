// shadertype=glsl

#version 430

layout(location = 0) uniform sampler2D drawnM;
layout(location = 1) uniform sampler2D glowM;

out vec4 outColor;

in vec2 vUV;

void main()
{
	outColor = texture(drawnM, vUV) + texture(glowM, vUV);
}

