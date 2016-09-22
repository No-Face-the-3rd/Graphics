// shadertype=glsl

#version 430

layout(location = 0) uniform sampler2D blurTarg;
layout(location = 1) uniform int blurRange;

layout(location = 0) in vec2 UV;

layout(location = 0) out vec4 outColor;

vec4 cBlur(in sampler2D map, in vec2 UV, in int bRange);

void main()
{
	outColor = cBlur(blurTarg, UV, blurRange);

}

vec4 cBlur(in sampler2D map, in vec2 UV, in int bRange)
{
	vec4 ret = texture(map, UV);
	vec2 texel = 1.0f / textureSize(map, 0).xy;
	
	for(int i = -bRange; i < bRange;i++)
	{
		ret += texture(map, UV + vec2(i, 0) * texel);
		ret += texture(map, UV + vec2(0, i) * texel);
	}

	return ret / (bRange * 4);
}