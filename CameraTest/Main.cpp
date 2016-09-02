

#include "window.h"
#include "gallery.h"
#include "timeManager.h"
#include "input.h"
#include "camera.h"


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


	gallery.loadShader("simple", "../res/shaders/simple.vs", "../res/shaders/simple.fs");
	gallery.loadShader("camera", "../res/shaders/camera.vs", "../res/shaders/camera.fs");
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

		

		//draw(gallery.getShader("simple"), gallery.getGeometry("cube"));

		model = glm::rotate(curTime, glm::vec3(1.0f - fmod(curTime,1.0f), fmod(curTime,1.0f), fmod(curTime,1.0f)/0.5f));

		draw(gallery.getShader("camera"), gallery.getGeometry("cube"), glm::value_ptr(glm::rotate(curTime, glm::vec3(0,-fmod(curTime,1.0f),0)) * model), glm::value_ptr(view), glm::value_ptr(proj));
		draw(gallery.getShader("camera"), gallery.getGeometry("sphere"),  glm::value_ptr(glm::translate(glm::vec3(1.0f, 1.0f, 1.0f)) * model * glm::translate(glm::vec3(1.0f, 1.0f, 1.0f)) ), glm::value_ptr(view), glm::value_ptr(proj));
		draw(gallery.getShader("camera"), gallery.getGeometry("sphere"), glm::value_ptr(model * glm::translate(glm::vec3(1.0f,0.0f,-1.0f))), glm::value_ptr(view), glm::value_ptr(proj));


		draw(gallery.getShader("camera"), gallery.getGeometry("cube"), glm::value_ptr(glm::rotate(curTime,glm::vec3(0.0f,fmod(curTime,1.0f),0.0f)) * model * glm::translate(glm::vec3(3.0f, 1.0f, 0.0f))), glm::value_ptr(view), glm::value_ptr(proj));
		float test = fabs(fmod(curTime / 6.0f, 6.0f));
		if (test < 1.0f)
		{
			moveX = -3.0f + fmod(curTime, 6.0f);
		}
		else if (test > 1.0f && test < 2.0f)
		{
			moveY = -3.0f + fmod(curTime, 6.0f);
		}
		else if (test > 2.0f && test < 3.0f)
		{
			moveZ = -3.0f + fmod(curTime, 6.0f);
		}
		else if (test > 3.0f && test < 4.0f)
		{
			moveX = 3.0f - fmod(curTime, 6.0f);
		}
		else if (test > 4.0f && test < 5.0f)
		{
			moveY = 3.0f - fmod(curTime, 6.0f);
		}
		else
		{
			moveZ = 4.0f - fmod(curTime, 10.0f);
		}
		glm::mat4 modelo = glm::translate(glm::vec3(moveX, moveY, moveZ));
		draw(gallery.getShader("camera"), gallery.getGeometry("cube"), glm::value_ptr(modelo), glm::value_ptr(view), glm::value_ptr(proj));
	}

	input.term();
	timer.term();
	gallery.term();
	window.term();

	return;
}