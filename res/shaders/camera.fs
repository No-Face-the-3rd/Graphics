#version 330

in vec4 vColor;
in vec4 vPosition;

out vec4 outColor;


void main()
{

	if(vColor != vec4(0,0,0,0))
	{
		outColor = vColor;
	}
	else
	{
		outColor = vec4(1,1,1,1);
		outColor.r = cos(vPosition.x);
		outColor.g = -cos(vPosition.y);
		outColor.b = cos(vPosition.z);
	}

}
