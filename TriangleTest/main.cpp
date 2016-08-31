

#include "window.h"
#include "gallery.h"
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


	float time = 0;
	while (window.step())
	{
		time += 0.1666f;
		draw(gallery.getShader("simple"), gallery.getGeometry("cube"), time);
		draw(gallery.getShader("simple"), gallery.getGeometry("sphere"), time);
	}


	gallery.term();
	window.term();

	return;
}
