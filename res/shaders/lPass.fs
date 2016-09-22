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
layout(location = 8) uniform sampler2D depthM;

layout(location = 9) uniform vec4 lDir = normalize(vec4(-1,-1,-1,0));

layout(location = 0) out vec4 outColor;
layout(location = 1) out vec4 outAlbedo;
layout(location = 2) out vec4 outSpec;


void main()
{

	vec3 light = normalize((view * lDir).xyz);
	vec3 normal = normalize(texture(normalM, UV).xyz);

	vec3 reflection = reflect(light, normal);


	vec3 E = -normalize(texture(positionM, UV).xyz);

	float specPow = 32.0f;

	float lamb = max(0,-dot(light, normal));
	float spec = max(0,-dot(E, reflection));
	if(spec > 0)
	{
		spec = pow(spec, specPow);
	}

	outAlbedo = texture(albedoM, UV) * lamb;
	outSpec = texture(specM, UV) * spec;
	outColor = outAlbedo + outSpec;
}


