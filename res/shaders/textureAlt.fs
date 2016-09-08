#version 430

in vec4 vColor;
in vec4 vPosition;
in vec2 vTexCoord;

out vec4 outColor;

layout(location = 0) uniform mat4 projection;
layout(location = 1) uniform mat4 view;
layout(location = 2) uniform mat4 model;
layout(location = 3) uniform float time = 0.0f;

layout(location = 4) uniform sampler2D tex;

void main()
{


		if(vColor != vec4(0,0,0,0))
		{
			outColor = vColor;
		}
		else
		{
			outColor = vec4(1,1,1,1);
			outColor = view * model * outColor * cos(time * vPosition.z);
			vec4 blahPosition =  view * model * vPosition;
			if(blahPosition.y > 0.0)
			outColor *= texture(tex,blahPosition.xy);
			if(blahPosition.x > 0.0)
			outColor = outColor * (vec4(1,1,1,1) - texture(tex,blahPosition.xy));
		}
	vec4 bler = projection *  view * model * vPosition;
	float mew = (bler.z / bler.w) * 100 - 99;
	float blah = texture(tex,vTexCoord).r;

	vec4 meow = vec4(mew, mew, blah + mew,1.0f);




	outColor = vColor * texture(tex,vTexCoord);
	outColor = meow;



}
