

#include "window.h"
#include "gallery.h"
#include "timeManager.h"
#include "input.h"
#include "camera.h"
#include "procgen.h"


#include "glm\glm.hpp"
#include "glm\ext.hpp"

#include <math.h>
// This is in a develop branch!

void main()
{
	Window window;
	gallery gallery;
	timer timer;
	input input;
	camera cam;

	window.init(1360, 768);
	gallery.init();
	input.init(window);
	timer.init();

	gallery.generatePlane("meow", 64, 64);

	Geometry purple = genGrid(512, 75);

	unsigned char pixels[] ={125,125,0};
	Texture tex2 = makeTexture(1, 1, 0x1907, pixels);
	Texture tex = loadTexture("../res/textures/meow.jpg");
	Texture tex3 = loadTexture("../res/textures/MewMap.jpg");
	Texture tex4 = genNoise(512, 1);

	gallery.loadShader("simple", "../res/shaders/simple.vs", "../res/shaders/simple.fs");
	gallery.loadShader("camera", "../res/shaders/camera.vs", "../res/shaders/camera.fs");
	gallery.loadShader("texture", "../res/shaders/texture.vs", "../res/shaders/texture.fs");
	gallery.loadShader("texture2", "../res/shaders/textureAlt.vs", "../res/shaders/textureAlt.fs");

	gallery.loadObjectOBJ("cube", "../res/models/cube.obj");
	gallery.loadObjectOBJ("sphere", "../res/models/sphere.obj");


	float ident[16] = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };

	glm::mat4 proj, view, model;


	proj = glm::perspective(45.0f, 1.0f, 0.10f, 20.0f);

	view = glm::lookAt(glm::vec3(5.0f, 5.0f , 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,1.0f, 0.0f));
	//model = glm::translate(glm::vec3(0.0f,0.0f,0.0f));
	cam.jumpTo(glm::vec3(5.0f, 5.0f, 5.0f));
	cam.lookAt(glm::vec3(0.0f, 0.0f, 0.0f));

	float curTime = 0.0f;

	float moveX = -3.0f, moveY = -3.0f, moveZ = -3.0f;
	while (window.step())
	{
		timer.step();
		input.step();
		

		view = cam.getView();
		proj = cam.getProjection();

		cam.update(input,timer);


		curTime = timer.getTime();

		


		model = glm::rotate(curTime, glm::vec3(1.0f - fmod(curTime,1.0f), fmod(curTime,1.0f), fmod(curTime,1.0f)/0.5f));

		//draw(gallery.getShader("texture"), gallery.getGeometry("cube"), tex, glm::value_ptr(glm::rotate(curTime, glm::vec3(0, -fmod(curTime, 1.0f), 0)) * model), glm::value_ptr(view), glm::value_ptr(proj),curTime);
		//draw(gallery.getShader("texture"), gallery.getGeometry("sphere"),tex,  glm::value_ptr(glm::translate(glm::vec3(1.0f, 1.0f, 1.0f)) * model * glm::translate(glm::vec3(1.0f, 1.0f, 1.0f)) ), glm::value_ptr(view), glm::value_ptr(proj),curTime);
		//draw(gallery.getShader("texture"), gallery.getGeometry("sphere"), tex, glm::value_ptr(model * glm::translate(glm::vec3(1.0f, 0.0f, -1.0f))), glm::value_ptr(view), glm::value_ptr(proj), curTime);


		glm::mat4 mod2;
		mod2 = glm::scale(glm::vec3(0.5f,1.0f,0.5f)) * glm::translate(glm::vec3(-32.0f, -5.0f, -32.0f));

		//draw(gallery.getShader("texture2"), gallery.getGeometry("meow"), tex3, glm::value_ptr(mod2), glm::value_ptr(view), glm::value_ptr(proj), curTime);
		draw(gallery.getShader("texture2"), purple, tex4, glm::value_ptr(mod2), glm::value_ptr(view), glm::value_ptr(proj), curTime);


		//draw(gallery.getShader("texture"), gallery.getGeometry("cube"), tex, glm::value_ptr(glm::rotate(curTime, glm::vec3(0.0f, fmod(curTime, 1.0f), 0.0f)) * model * glm::translate(glm::vec3(3.0f, 1.0f, 0.0f))), glm::value_ptr(view), glm::value_ptr(proj), curTime);
		//float test = fabs(fmod(curTime / 6.0f, 6.0f));
		//if (test < 1.0f)
		{
			//moveX = -3.0f + fmod(curTime, 6.0f);
		}
		//else if (test > 1.0f && test < 2.0f)
		{
			//moveY = -3.0f + fmod(curTime, 6.0f);
		}
		//else if (test > 2.0f && test < 3.0f)
		{
			//moveZ = -3.0f + fmod(curTime, 6.0f);
		}
		//else if (test > 3.0f && test < 4.0f)
		{
			//moveX = 3.0f - fmod(curTime, 6.0f);
		}
		//else if (test > 4.0f && test < 5.0f)
		{
			//moveY = 3.0f - fmod(curTime, 6.0f);
		}
		//else
		{
			//moveZ = 4.0f - fmod(curTime, 10.0f);
		}
		//glm::mat4 modelo = glm::translate(glm::vec3(moveX, moveY, moveZ));
		//draw(gallery.getShader("texture"), gallery.getGeometry("cube"),tex, glm::value_ptr(modelo), glm::value_ptr(view), glm::value_ptr(proj),curTime);
	}

	freeTexture(tex);

	input.term();
	timer.term();
	gallery.term();
	window.term();

	return;
}
