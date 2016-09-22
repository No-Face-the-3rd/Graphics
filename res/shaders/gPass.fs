// shadertype=glsl

#version 430

in vec4 vPosition;
in vec4 vColor;
in vec4 vNormal;
in vec2 UV;


layout(location = 0)out vec4 outAlbedo;
layout(location = 1)out vec4 outNormal;
layout(location = 2)out vec4 outSpecular;
layout(location = 3)out vec4 outPosition;

layout(location = 0) uniform mat4 model;
layout(location = 1) uniform mat4 view;
layout(location = 2) uniform mat4 proj;
layout(location = 3) uniform float time;

layout(location = 4) uniform sampler2D diffM;
layout(location = 5) uniform sampler2D normalM;
layout(location = 6) uniform sampler2D specM;



mat3 cotangent_frame(in vec3 n, in vec3 p, in vec2 uv);

void main()
{


	vec4 posit = vPosition;
	vec4 norm = vNormal;

	mat3 TBN = cotangent_frame(norm.xyz, posit.xyz,UV);

	norm = vec4( (TBN * (2.0f * texture(normalM, UV).xyz - 1.0f)), 1.0f );

	outAlbedo = texture(diffM, UV);
	outNormal = vec4(norm.xyz,0);
	outSpecular = texture(specM, UV);
	outPosition = posit;
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

	float invMax = inversesqrt(max(dot(t,t),dot(b,b)));

	return mat3(t * invMax, b * invMax, n);
}
