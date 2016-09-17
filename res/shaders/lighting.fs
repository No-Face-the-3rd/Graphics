// shadertype=glsl

#version 430

in vec4 vPosition;
in vec4 vColor;
in vec4 vNormal;
in vec2 UV;


layout(location = 0)out vec4 outColor;
layout(location = 1)out vec4 outDiffuse;
layout(location = 2)out vec4 outSpecular;

layout(location = 0) uniform mat4 model;
layout(location = 1) uniform mat4 view;
layout(location = 2) uniform mat4 proj;
layout(location = 3) uniform float time;

layout(location = 4) uniform sampler2D diffM;
layout(location = 5) uniform sampler2D normalM;
layout(location = 6) uniform sampler2D specM;

layout(location = 7) uniform vec4 lightDir;
layout(location = 8) uniform vec4 lightAmb;
layout(location = 9) uniform vec4 lightDif;
layout(location = 10) uniform vec4 lightSpec;

layout(location = 11) uniform vec4 surfAmb;
layout(location = 12) uniform vec4 surfDif;
layout(location = 13) uniform vec4 surfSpec;

layout(location = 14) uniform float specPow;


mat3 cotangent_frame(in vec3 n, in vec3 p, in vec2 uv);

void main()
{
	vec4 lightDir = normalize(vec4(-1.0f,-1.0f,-1.0f,0.0f));
	vec4 lightAmb = vec4(0.1f,0.1f,0.4f,1.0f);
	vec4 lightDif = vec4(1.0f,1.0f,1.0f,1.0f);
	vec4 lightSpec = vec4(0.5f,0.5f,0.5f,1.0f);

	vec4 surfAmb = vec4(0.1f,0.1f,0.1f,1.0f);
	vec4 surfDif = texture(diffM,UV);
	vec4 surfSpec = texture(specM,UV);
	

	float specPow = 32.0f;

	vec4 camPos = inverse(view)[3];

	vec4 posit = vPosition;
	vec4 norm = vNormal;

	mat3 TBN = cotangent_frame(norm.xyz, posit.xyz,UV);

	norm = vec4( (TBN * (2.0f * texture(normalM, UV).xyz - 1.0f)), 1.0f );


	vec4 R = reflect(lightDir, norm);
	vec4 E = normalize(camPos - posit);

	float lamb = max(0.0f, -dot(lightDir, norm));
	
	float spec = pow(max(0.0f,dot(E, R)), specPow);
	
	vec4 ambient = lightAmb * surfAmb;
	outDiffuse = lightDif * lamb * surfDif;
	outSpecular = lightSpec * spec * surfSpec;

	outColor =  ( ambient + outDiffuse + outSpecular);


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

