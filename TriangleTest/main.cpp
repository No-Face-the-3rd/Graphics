

#include "crenderutils.h"
#include "window.h"
#include "Vertex.h"
// This is in a develop branch!

void main()
{
	Window window;
	window.init();
	

	Vertex verts[4] = { {1.0f,0.0f,0.0f,1.0f,1.0f,0.0f,0.0f,1.0f}, {-1.0f,0.0f,0.0f,1.0f,1.0f,0.0f,1.0f,1.0f}, {-1.0f,-1.0f,0.0f,1.0f,1.0f,1.0f,0.0f,1.0f},{1.0f,-1.0f,0.0f,1.0f,0.2f,0.2f,0.0f,1.0f} };

	unsigned tris[6] ={ 0,1,2,1,2,3 };

	const char vsource[] = "#version 330\n""layout(location = 0)in vec4 position;""layout(location = 1)in vec4 color;""out vec4 vColor;""void main() { gl_Position = position; vColor = color; } ";
	const char fsource[] = "#version 150\n""out vec4 outColor;""in vec4 vColor;""void main() { outColor = vColor; }";
	Geometry geo = makeGeometry(verts, 4, tris,6);
	Shader shader = makeShader(vsource, fsource);

	while (window.step())
	{


		draw(shader, geo);

	}

	freeGeometry(geo);
	freeShader(shader);

	window.term();

	return;
}
