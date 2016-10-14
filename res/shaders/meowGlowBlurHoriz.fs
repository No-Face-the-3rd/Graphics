// shadertype=glsl

#version 430

in vec2 vUV;

layout(location = 0) uniform sampler2D blurM;
layout(location = 1) uniform int blurStrength = 3;

layout(location = 0) out vec4 outColor;

void main()
{
	vec2 texel = vec2(1.0f / textureSize(blurM, 0 ).x, 0.0f);
	outColor = texture(blurM, vUV);
	int count = 1;
	for(int i = 0; i < blurStrength;i++)
	{
		outColor += texture(blurM, vUV + i * texel);
		outColor += texture(blurM, vUV - i * texel);
		count += 2;
	}
	outColor /= count;
}