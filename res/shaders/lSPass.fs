// shadertype=glsl

#version 430

in vec2 UV;

layout(location = 0) uniform mat4 model;
layout(location = 1) uniform mat4 view;
layout(location = 2) uniform mat4 proj;
layout(location = 3) uniform float time;

layout(location = 4) uniform sampler2D albedoM;
layout(location = 5) uniform sampler2D normalM;
layout(location = 6) uniform sampler2D specM;
layout(location = 7) uniform sampler2D positionM;
layout(location = 8) uniform sampler2D shadowM;

layout(location = 9) uniform vec4 lCol;
layout(location = 10) uniform mat4 lView;
layout(location = 11) uniform mat4 lProj;
uniform float shadowBias = 0.1f;

layout(location = 0) out vec4 outColor;
layout(location = 1) out vec4 outAlbedo;
layout(location = 2) out vec4 outSpec;

uniform mat4 clipToUV = mat4(0.5f, 0.0f,0.0f,0.0f,0.0f,0.5f,0.0f,0.0f,0.0f,0.0f,0.5f,0.0f,0.5f,0.5f,0.5f,1.0f);

void main()
{

	vec3 light = normalize((view * lView[2]).xyz);
	vec3 normal = normalize(texture(normalM, UV).xyz);
	vec4 P = texture(positionM, UV);

	vec4 sUV = clipToUV * lProj * lView * inverse(view) * vec4(P.xyz, 1);

	if(texture(shadowM, sUV.xy).r < sUV.z - shadowBias)
		discard;

	vec3 reflection = reflect(light, normal);


	vec3 E = normalize(view[3].xyz + P.xyz);

	float specPow = 32.0f;

	float lamb = max(0,-dot(light, normal));
	float spec = max(0,-dot(E, reflection));
	if(spec > 0)
	{
		spec = pow(spec, specPow);
	}

	outAlbedo = texture(albedoM, UV) * lamb * lCol;
	outSpec = texture(specM, UV) * spec * lCol;
	outColor = outAlbedo + outSpec;
}


