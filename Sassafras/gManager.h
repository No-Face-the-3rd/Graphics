#pragma once


#ifndef G_MANAGER_H
#define G_MANAGER_H

#include "window.h"
#include "gallery.h"
#include "timeManager.h"
#include "input.h"
#include "camera.h"

#include "object.h"



class gManager
{
public:
	Window window;
	gallery gallery;
	timer timer;
	input input;
	camera cam;
	unsigned screenWidth, screenHeight;

	std::vector<obJect> objects;
	std::vector<dirLight> dirLights;

	glm::mat4 lightProj;
	glm::vec3 ambLight;

	std::string name;

	gManager(unsigned width, unsigned height, const char *name = "Sassafras");


	bool init();
	bool step();
	bool draw();
	bool term();
	
private:
	void initCam();
	void initTextures();
	void initShaders();
	void initGeometry();
	void initFrameBuffers();
	void initLights();
	void initObjects();

	void stepObjects();
};


#endif
