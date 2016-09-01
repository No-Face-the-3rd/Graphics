

#include "window.h"
#include "gallery.h"


#include "glm\glm.hpp"
#include "glm\ext.hpp"

#include <math.h>
// This is in a develop branch!

void main()
{
	Window window;
	gallery gallery;

	window.init(800, 800);
	gallery.init();


	gallery.loadShader("simple", "../res/shaders/simple.vs", "../res/shaders/simple.fs");
	gallery.loadShader("camera", "../res/shaders/camera.vs", "../res/shaders/camera.fs");
	gallery.loadObjectOBJ("cube", "../res/models/cube.obj");
	gallery.loadObjectOBJ("sphere", "../res/models/sphere.obj");


	float ident[16] = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };

	glm::mat4 proj, view, model;


	proj = glm::perspective(45.0f, 1.0f, 0.10f, 20.0f);

	//view = glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(5, 5, 5), glm::vec3(0, 1, 0));

	float time = 0;
	while (window.step())
	{
		time += 0.01666f;

	view = glm::lookAt(glm::vec3(5, 5 , 5), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,1.0f, 0.0f));
		//draw(gallery.getShader("simple"), gallery.getGeometry("cube"));

		model = glm::rotate(time, glm::vec3(1.0f - fmod(time,1.0f), fmod(time,1.0f), fmod(time,1.0f)/0.5f));

		draw(gallery.getShader("camera"), gallery.getGeometry("cube"), glm::value_ptr(glm::rotate(time, glm::vec3(0,-fmod(time,1.0f),0)) * model), glm::value_ptr(view), glm::value_ptr(proj));
		draw(gallery.getShader("camera"), gallery.getGeometry("sphere"),  glm::value_ptr(glm::translate(glm::vec3(1.0f, 1.0f, 1.0f)) * model * glm::translate(glm::vec3(1.0f, 1.0f, 1.0f)) ), glm::value_ptr(view), glm::value_ptr(proj));
		draw(gallery.getShader("camera"), gallery.getGeometry("sphere"), glm::value_ptr(model * glm::translate(glm::vec3(1.0f,0.0f,-1.0f))), glm::value_ptr(view), glm::value_ptr(proj));


		draw(gallery.getShader("camera"), gallery.getGeometry("cube"), glm::value_ptr(glm::rotate(time,glm::vec3(0.0f,fmod(time,1.0f),0.0f)) * model * glm::translate(glm::vec3(3.0f, 1.0f, 0.0f))), glm::value_ptr(view), glm::value_ptr(proj));


	}


	gallery.term();
	window.term();

	return;
}
