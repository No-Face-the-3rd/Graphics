#include "gManager.h"


gManager::gManager(unsigned width, unsigned height, const char *name)
{
	screenWidth = width;
	screenHeight = height;
	this->name = std::string(name);
}

bool gManager::init()
{
	window.init(screenWidth, screenHeight, name.c_str());
	gallery.init();
	timer.init();
	input.init(window);
	
	initTextures();
	initShaders();
	initGeometry();
	initFrameBuffers();

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

}

void gManager::initGeometry()
{
}

void gManager::initFrameBuffers()
{

}

