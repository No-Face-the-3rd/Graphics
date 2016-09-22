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

#define PI 3.14159265358979f



void main()
{

	const int div = 36;
	float scale = 2.0f;

	vec2 iUV = UV + vec2(cos(UV.y + time) / scale, sin(UV.x + time) / scale);

	vec2 texel = 1.0f / textureSize(diffM, 0 ).xy;

	//iUV = UV;
	


	vec4 o[div];

	for(int i = 0;i < div;i++)
	{
		float bleh = cos(time * (i % 2));
		if(i % 3 == 0)
			bleh *= cos(time * (i % 4));
		if(i % 4 == 0)
			bleh *= cos(time * (i % 5));
		float xOff = cos(bleh) * cos( (time + i * 360 / div * PI / 180.0f) ) / scale;
		float yOff = cos(bleh) * sin( (time + i * 360 / div * PI / 180.0f) ) / scale;
		vec2 offSet = vec2(xOff, yOff);
		vec4 xColori = texture(diffM, iUV + offSet + vec2(1,1) * texel) + texture(diffM, iUV + offSet + vec2(1,0) * texel) * 2 + texture(diffM, iUV + offSet + vec2(1,-1) * texel) - texture(diffM, iUV + offSet + vec2(-1,1)) - texture(diffM, iUV + offSet + vec2(-1, 0)) * 2 - texture(diffM, iUV + offSet + vec2(-1,-1));
		vec4 yColori = texture(diffM, iUV + offSet + vec2(1,-1) * texel) + texture(diffM, iUV + offSet + vec2(0,-1) * texel) * 2 + texture(diffM, iUV + offSet + vec2(-1,-1) * texel) - texture(diffM, iUV + offSet + vec2(-1,1)) - texture(diffM, iUV + offSet + vec2(0 , 1)) * 2 - texture(diffM, iUV + offSet + vec2(-1,-1));

		o[i] = texture(diffM, iUV + vec2( xOff, yOff )) - sqrt(xColori * xColori + yColori * yColori);
	}


	
	vec4 xColor = texture(diffM, iUV + vec2(1,1) * texel) + texture(diffM, iUV + vec2(1,0) * texel) * 2 + texture(diffM, iUV + vec2(1,-1) * texel) - texture(diffM, iUV + vec2(-1,1)) - texture(diffM, iUV + vec2(-1, 0)) * 2 - texture(diffM, iUV + vec2(-1,-1));
	vec4 yColor = texture(diffM, iUV + vec2(1,-1) * texel) + texture(diffM, iUV + vec2(0,-1) * texel) * 2 + texture(diffM, iUV + vec2(-1,-1) * texel) - texture(diffM, iUV + vec2(-1,1)) - texture(diffM, iUV + vec2(0 , 1)) * 2 - texture(diffM, iUV + vec2(-1,-1));

	outColor = texture(diffM, iUV) + sqrt(xColor * xColor + yColor * yColor);
	int num = 1;

	for(int i = 0;i < div;i++)
		if(o[i] != vec4(0,0,0,0))
			{
				outColor += o[i];
				num++;			
			}

	outColor /= num;

}

