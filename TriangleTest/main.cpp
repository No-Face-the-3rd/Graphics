

#include "window.h"
#include "gallery.h"

#include "crenderutils.h"
// This is in a develop branch!

void main()
{
	Window window;
	gallery gallery;

	window.init(800,800);
	gallery.init();
	

	gallery.loadShader("simple", "../res/shaders/simple.vs", "../res/shaders/simple.fs");
	gallery.loadObjectOBJ("cube", "../res/models/cube.obj");
	gallery.loadObjectOBJ("sphere", "../res/models/sphere.obj");

	gallery.makeGeometry("quad", quadVerts, 4, quadTris, 6);

	frameBuffer screen = { 0,800,800 };
	int meow = 0;
	float time = 0;
	while (window.step())
	{
		time += 0.01666f;
		meow++;
		tDraw(gallery.getShader("simple"), gallery.getGeometry("quad"), screen);
	}


	gallery.term();
	window.term();

	return;
}
