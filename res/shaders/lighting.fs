#version 430

in vec4 vColor;
in vec4 vPosition;
in vec4 vNormal;
in vec2 UV;


out vec4 outColor;

layout(location = 0) uniform mat4 projection;
layout(location = 1) uniform mat4 view;
layout(location = 2) uniform mat4 model;
layout(location = 3) uniform float time;

layout(location = 4) uniform vec4 lightDir;
layout(location = 5) uniform vec4 lightAmb;
layout(location = 6) uniform vec4 lightDif;
layout(location = 7) uniform vec4 lightSpec;

layout(location = 8) uniform vec4 surfAmb;
layout(location = 9) uniform vec4 surfDif;
layout(location = 10) uniform vec4 surfSpec;

layout(location = 11) uniform float specPow;

layout(location = 12) uniform sampler2D diffM;
layout(location = 13) uniform sampler2D normalM;
layout(location = 14) uniform sampler2D specM;


void main()
{
	vec4 lightDir = normalize(vec4(-1.0f,-1.0f,-1.0f,0.0f));
	vec4 lightAmb = vec4(0.4f,0.4f,0.4f,1.0f);
	vec4 lightDif = vec4(1.0f,1.0f,1.0f,1.0f);
	vec4 lightSpec = vec4(1.0f,1.0f,1.0f,1.0f);

	vec4 surfAmb = vec4(0.4f,0.4f,0.4f,1.0f);
	vec4 surfDif = texture(diffM,UV);
	vec4 surfSpec = texture(specM,UV);
	
	float specPow = 8.0f;

	vec4 camPos = inverse(view)[3];

	vec4 norm = model * vNormal;
	vec4 posit = model * vPosition;

	vec4 R = reflect(lightDir, norm);
	vec4 E = normalize(camPos - posit);

	float lamb = max(0.0f, -dot(norm,lightDir));
	
	float spec = pow(max(0.0f,dot(R, E)), specPow);
	
	vec4 ambient = lightAmb * surfAmb;
	vec4 diffuse = lightDif * lamb * surfDif;
	vec4 specular = lightSpec * spec * surfSpec;


	outColor =  ambient + diffuse + specular;



}
