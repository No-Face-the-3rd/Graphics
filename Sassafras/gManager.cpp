#include "gManager.h"

#include "glm\ext.hpp"
gManager::gManager(unsigned width, unsigned height, const char *name)
{
	screenWidth = width;
	screenHeight = height;
	this->name = std::string(name);
}

bool gManager::init()
{
	window.init(screenWidth, screenHeight, name.c_str());
	gallery.init(screenWidth, screenHeight);
	timer.init();
	input.init(window);
	
	initTextures();
	initShaders();
	initGeometry();
	initFrameBuffers();
	initObjects();

	return true;
}

bool gManager::step()
{
	bool ret = window.step();
	timer.step();
	input.step();
	cam.update(input, timer);
	return ret;
}

bool gManager::draw()
{
	for each(auto object in objects)
	{
		tDraw(gallery.getShader("meowGPass"), gallery.getGeometry(object.geometry.c_str()), gallery.getFrameBuffer("meowGFrame"), object.model(), cam.getView(), cam.getProjection(), object.opacity, gallery.getTexture(object.textures.at(0).c_str()), gallery.getTexture(object.textures.at(1).c_str()), gallery.getTexture(object.textures.at(2).c_str()), gallery.getTexture(object.textures.at(3).c_str()));
	}

	tDraw(gallery.getShader("meowToScreen"), gallery.getGeometry("quad"), gallery.getFrameBuffer("screen"), gallery.getFrameBuffer("meowGFrame").colors[0]);

	return true;
}

bool gManager::term()
{
	input.term();
	timer.term();
	gallery.term();
	window.term();
	return true;
}

void gManager::initTextures()
{
	unsigned char blackPixels[] = { 0,0,0 };
	gallery.makeTexture("black", 1, 1, 4, blackPixels, false);
	gallery.loadTexture("meow", "../res/textures/meow.jpg");
	gallery.loadTexture("mew", "../res/textures/MewMap.jpg");
	gallery.loadTexture("spearDif", "../res/textures/soulspear_diffuse.tga");
	gallery.loadTexture("spearNorm", "../res/textures/soulspear_normal.tga");
	gallery.loadTexture("spearSpec", "../res/textures/soulspear_specular.tga");
	gallery.loadTexture("spearGlow", "../res/textures/soulspear_glow.tga");
}

void gManager::initShaders()
{
	gallery.loadShader("meowGPass", "../res/shaders/meowGPass.vs", "../res/shaders/meowGPass.fs");
	gallery.loadShader("meowToFrame", "../res/shaders/meowToScreen.vs", "../res/shaders/meowToScreen.fs");
}

void gManager::initGeometry()
{
	gallery.loadObjectOBJ("cube", "../res/models/cube.obj");
	gallery.loadObjectOBJ("sphere", "../res/models/sphere.obj");
	gallery.loadObjectOBJ("spear", "../res/models/soulspear.obj");
	gallery.makeGeometry("quad", quadVerts, 4, quadTris, 6);
}

void gManager::initFrameBuffers()
{
	bool floatTex[] = { false, true, false, true, true };
	gallery.makeFrameBuffer("meowGFrame", screenWidth, screenHeight, 5, floatTex);
}

void gManager::initLights()
{
	ambLight = glm::vec3(0.1f, 0.1f, 0.2f);
	lightProj = glm::ortho<float>(-10, 10, -10, 10, -10, 10);
}

void gManager::initObjects()
{
	obJect tmp = obJect(glm::vec3());
	tmp.setTextures("meow");
	objects.push_back(tmp);
}
