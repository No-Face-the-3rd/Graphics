// shadertype=glsl

#version 430

in vec4 vPos;
in vec4 vNorm;
in vec2 vUV;

layout(location = 0) out vec4 outAlbedo;
layout(location = 1) out vec4 outNorm;
layout(location = 2) out vec4 outSpec;
layout(location = 3) out vec4 outPos;
layout(location = 4) out vec4 outGlow;


layout(location = 0) uniform mat4 model;
layout(location = 1) uniform mat4 view;
layout(location = 2) uniform mat4 proj;
layout(location = 3) uniform float opacity;

layout(location = 4) uniform sampler2D diffM;
layout(location = 5) uniform sampler2D normalM;
layout(location = 6) uniform sampler2D specM;
layout(location = 7) uniform sampler2D glowM;

mat3 cotangent_frame(in vec3 n, in vec3 p, in vec2 uv);

void main()
{
	vec4 posit = vPos;
	vec4 norm = vNorm;

	
	mat3 TBN = cotangent_frame(norm.xyz, posit.xyz, vUV);

	norm = vec4((TBN * (2.0f * texture(normalM, vUV).xyz - 1.0f)), 1.0f);

	outAlbedo = texture(diffM, vUV);
	outNorm = vec4(norm.xyz, 0);
	outSpec = texture(specM, vUV);
	outPos = posit;
	outGlow = texture(glowM, vUV);
	outAlbedo.a = outNorm.a = outSpec.a = outGlow.a = opacity;
}

mat3 cotangent_frame(in vec3 n, in vec3 p, in vec2 uv)
{
	vec3 dp1 = dFdx(p);
	vec3 dp2 = dFdy(p);
	vec2 duv1 = dFdx(uv);
	vec2 duv2 = dFdy(uv);

	vec3 dp2perp = cross(dp2, n);
	vec3 dp1perp = cross(n, dp1);

	vec3 t = dp2perp * duv1.x + dp1perp * duv2.x;
	vec3 b = dp2perp * duv1.y + dp1perp * duv2.y;

	float invMax = inversesqrt(max(dot(t,t), dot(b,b)));

	return mat3(t * invMax, b * invMax, n);
}