// shadertype=glsl

#version 430

layout(location = 0) uniform mat4 view;

layout(location = 2) uniform sampler2D albedoM;
layout(location = 3) uniform sampler2D normalM;
layout(location = 4) uniform sampler2D specM;
layout(location = 5) uniform sampler2D positionM;
layout(location = 6) uniform sampler2D shadowM;

layout(location = 7) uniform vec4 lCol;
layout(location = 8) uniform mat4 lView;
layout(location = 9) uniform mat4 lProj;
layout(location = 10) uniform vec4 AmbCol;
layout(location = 11) uniform float shadowBias = 0.1f;

layout(location = 0) out vec4 outColor;

uniform mat4 clipToUV = mat4(0.5f, 0.0f,0.0f,0.0f,0.0f,0.5f,0.0f,0.0f,0.0f,0.0f,0.5f,0.0f,0.5f,0.5f,0.5f,1.0f);

in vec2 vUV;

void main()
{
	vec3 light = normalize((view * lView[2]).xyz);
	vec3 normal = normalize(texture(normalM, vUV).xyz);
	vec4 P = texture(positionM, vUV);

	vec4 sUV = clipToUV * lProj * lView * inverse(view) * vec4(P.xyz, 1);

	if(texture(shadowM, sUV.xy).r < sUV.z - shadowBias)
		discard;

	
	vec3 E = normalize(view[3].xyz + P.xyz);
	vec3 halfD = normalize(-E + light);

	float specPow = 16.0f;

	float lamb = max(0,-dot(light, normal));
	float spec = max(0, dot(normal, halfD));
	if(spec > 0)
	{
		spec = pow(spec, specPow);
	}

	vec4 calcAmb = AmbCol * texture(albedoM, vUV);
	vec4 calcAlbedo = texture(albedoM, vUV) * lamb * lCol;
	vec4 calcSpec = texture(specM, vUV) * spec * lCol;
	outColor = calcAmb + calcAlbedo + calcSpec;

}



