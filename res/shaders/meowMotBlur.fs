// shadertype=glsl

#version 430

in vec2 vUV;

layout(location = 0) uniform sampler2D prevFrame;
layout(location = 1) uniform sampler2D curFrame;
layout(location = 2) uniform float ratio;

layout(location = 0) out vec4 outColor;

void main()
{
	if(ratio <= 1 && ratio >= 0)
	{
		outColor = texture(prevFrame, vUV) * (1-ratio) + texture(curFrame, vUV) * ratio;
	}
	else
	{
		outColor = texture(curFrame, vUV);
	}
}
