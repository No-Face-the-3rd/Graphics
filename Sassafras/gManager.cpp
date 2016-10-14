#include "gManager.h"

#include "glm\ext.hpp"
#include <algorithm>
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
	
	initCam();

	initTextures();
	initShaders();
	initGeometry();
	initFrameBuffers();
	initObjects();
	initLights();

	return true;
}

bool gManager::step()
{
	bool ret = window.step();
	timer.step();
	input.step();
	cam.update(input, timer);
	stepObjects();
	std::sort(objects.begin(), objects.end(),cmpOp);
	return ret;
}

bool gManager::draw()
{
	clearFrameBuffer(gallery.getFrameBuffer("meowGFrame"));
	clearFrameBuffer(gallery.getFrameBuffer("meowGlHBlur"));
	clearFrameBuffer(gallery.getFrameBuffer("meowGlVBlur"));
	clearFrameBuffer(gallery.getFrameBuffer("meowCurFrame"));
	clearFrameBuffer(gallery.getFrameBuffer("meowMotBlur"));
	clearFrameBuffer(gallery.getFrameBuffer("meowLightPass"));
	clearFrameBuffer(gallery.getFrameBuffer("meowGlowCombPass"));
	glm::mat4 camView = cam.getView(), camProj = cam.getProjection();
	for each(auto object in objects)
	{
		glm::mat4 mod = object.model();
		Texture diff = gallery.getTexture(object.textures.at(0).c_str());
		Texture norm = gallery.getTexture(object.textures.at(1).c_str());
		Texture spec = gallery.getTexture(object.textures.at(2).c_str());
		Texture glow = gallery.getTexture(object.textures.at(3).c_str());
		tDraw(gallery.getShader("meowGPass"), gallery.getGeometry(object.geometry.c_str()), gallery.getFrameBuffer("meowGFrame"), mod, camView, camProj, object.opacity, diff, norm, spec, glow);
	}

	tDraw(gallery.getShader("meowGlowBlurHoriz"), gallery.getGeometry("quad"), gallery.getFrameBuffer("meowGlHBlur"), gallery.getFrameBuffer("meowGFrame").colors[4], 10);
	tDraw(gallery.getShader("meowGlowBlurVert"), gallery.getGeometry("quad"), gallery.getFrameBuffer("meowGlVBlur"), gallery.getFrameBuffer("meowGlHBlur").colors[0], 10);

	for each(auto light in dirLights)
	{
		clearFrameBuffer(gallery.getFrameBuffer("meowShadPass"));
		glm::mat4 lightView = light.view();
		if (light.castShadows)
		{
			for each(auto object in objects)
			{
				glm::mat4 mod = object.model();
				tDraw(gallery.getShader("meowShadPass"), gallery.getGeometry(object.geometry.c_str()), gallery.getFrameBuffer("meowShadPass"), mod, lightView, lightProj);
			}
		}
		tDraw(gallery.getShader("meowLightPass"), gallery.getGeometry("quad"), gallery.getFrameBuffer("meowLightPass"), camView, gallery.getFrameBuffer("meowGFrame").colors[0], gallery.getFrameBuffer("meowGFrame").colors[1], gallery.getFrameBuffer("meowGFrame").colors[2],gallery.getFrameBuffer("meowGFrame").colors[3], gallery.getFrameBuffer("meowShadPass").depth, glm::vec4(light.color,1.0f),lightView,lightProj,glm::vec4(ambLight, 1.0f));
	}

	tDraw(gallery.getShader("meowGlowCombPass"), gallery.getGeometry("quad"), gallery.getFrameBuffer("meowGlowCombPass"), gallery.getFrameBuffer("meowLightPass").colors[0], gallery.getFrameBuffer("meowGlVBlur").colors[0]);

	tDraw(gallery.getShader("meowMotBlur"), gallery.getGeometry("quad"), gallery.getFrameBuffer("meowMotBlur"), gallery.getFrameBuffer("meowPrevFrame").colors[0], gallery.getFrameBuffer("meowGlowCombPass").colors[0], 0.75f);

	tDraw(gallery.getShader("meowToFrame"), gallery.getGeometry("quad"), gallery.getFrameBuffer("meowCurFrame"), gallery.getFrameBuffer("meowMotBlur").colors[0]);
	//draw curFrame to prevFrame
	clearFrameBuffer(gallery.getFrameBuffer("meowPrevFrame"));
	tDraw(gallery.getShader("meowToFrame"), gallery.getGeometry("quad"), gallery.getFrameBuffer("meowPrevFrame"), gallery.getFrameBuffer("meowCurFrame").colors[0]);
	//draw to screen
	tDraw(gallery.getShader("meowToFrame"), gallery.getGeometry("quad"), gallery.getFrameBuffer("screen"), gallery.getFrameBuffer("meowCurFrame").colors[0]);

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

void gManager::initCam()
{
	cam.jumpTo(glm::vec3(5.0f, 5.0f, 5.0f));
	cam.lookAt(glm::vec3(0.0f, 0.0f, 0.0f));
}

void gManager::initTextures()
{
	unsigned char blackPixels[] = { 0,0,0,0 }, whitePixels[] = { 255,255,255,0 }, grayPixels[] = { 125,125,125,0 };
	gallery.makeTexture("black", 1, 1, 4, blackPixels, false);
	gallery.makeTexture("white", 1, 1, 4, whitePixels, false);
	gallery.makeTexture("gray", 1, 1, 4, grayPixels, false);
	gallery.loadTexture("meow", "../res/textures/meow.jpg");
	gallery.loadTexture("mew", "../res/textures/MewMap.jpg");
	gallery.loadTexture("spearDif", "../res/textures/soulspear_diffuse.tga");
	gallery.loadTexture("spearNorm", "../res/textures/soulspear_normal.tga");
	gallery.loadTexture("spearSpec", "../res/textures/soulspear_specular.tga");
	gallery.loadTexture("spearGlow", "../res/textures/soulspear_glow.tga");
}

void gManager::initShaders()
{
	gallery.loadShader("meowGPass", "../res/shaders/meowGPass.vs", "../res/shaders/meowGPass.fs", true, false, true, true);
	gallery.loadShader("meowToFrame", "../res/shaders/meowToScreen.vs", "../res/shaders/meowToScreen.fs", true, false, true, false);
	gallery.loadShader("meowGlowBlurHoriz", "../res/shaders/meowGlowBlurHoriz.vs", "../res/shaders/meowGlowBlurHoriz.fs");
	gallery.loadShader("meowGlowBlurVert", "../res/shaders/meowGlowBlurVert.vs", "../res/shaders/meowGlowBlurVert.fs");
	gallery.loadShader("meowMotBlur", "../res/shaders/meowMotBlur.vs", "../res/shaders/meowMotBlur.fs");
	gallery.loadShader("meowLightPass", "../res/shaders/meowLightPass.vs", "../res/shaders/meowLightPass.fs");
	gallery.loadShader("meowShadPass", "../res/shaders/meowShadPass.vs", "../res/shaders/meowShadPass.fs", true);
	gallery.loadShader("meowGlowCombPass", "../res/shaders/meowGlowCombPass.vs", "../res/shaders/meowGlowCombPass.fs");
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
	bool meowGTex[] = { false, true, false, true, true }, meowGlowBlurTex[] = { true };
	gallery.makeFrameBuffer("meowGFrame", screenWidth, screenHeight, 5, meowGTex);
	gallery.makeFrameBuffer("meowGlHBlur", screenWidth, screenHeight, 1, meowGlowBlurTex);
	gallery.makeFrameBuffer("meowGlVBlur", screenWidth, screenHeight, 1, meowGlowBlurTex);
	gallery.makeFrameBuffer("meowPrevFrame", screenWidth, screenHeight, 1, meowGlowBlurTex);
	gallery.makeFrameBuffer("meowCurFrame", screenWidth, screenHeight, 1, meowGlowBlurTex);
	gallery.makeFrameBuffer("meowMotBlur", screenWidth, screenHeight, 1, meowGlowBlurTex);
	gallery.makeFrameBuffer("meowLightPass", screenWidth, screenHeight, 1, meowGlowBlurTex);
	gallery.makeFrameBuffer("meowShadPass", screenWidth, screenHeight, 0);
	gallery.makeFrameBuffer("meowGlowCombPass", screenWidth, screenHeight, 1, meowGlowBlurTex);
}

void gManager::initLights()
{
	ambLight = glm::vec3(0.3f, 0.3f, 0.3f);
	lightProj = glm::ortho<float>(-20, 20, -20, 20, -20, 20);
	dirLight meow;
	meow.dir = glm::vec3(-1.0f, -1.0f, -1.0f);
	meow.color = glm::vec3(1.0f, 1.0f, 1.0f);
	meow.castShadows = true;
	dirLights.push_back(meow);
	meow.dir = glm::vec3(1.0f, 1.0f, 1.0f);
	meow.color = glm::vec3(1.0f, 1.0f, 1.0f);
	meow.castShadows = false;
	dirLights.push_back(meow);
}

void gManager::initObjects()
{
	obJect tmp = obJect(glm::vec3());
	tmp.setTextures("meow", "meow", "meow", "meow");
	tmp.opacity = 1.0f;
	objects.push_back(tmp);
	obJect tmp2 = obJect(glm::vec3(0.0f,0.0f,2.0f));
	tmp2.setTextures("meow", "meow", "meow", "gray");
	tmp2.geometry = "cube";
	tmp2.opacity = 0.75f;
	objects.push_back(tmp2);
	tmp.position = glm::vec3(0.0f, 0.0f, 4.0f);
	objects.push_back(tmp);
	tmp2.position = glm::vec3(0.0f, 0.0f, 6.0f);
	tmp2.angularVel = glm::vec3(0.25f, 0.33f, 0.58f);
	tmp2.setTextures("mew", "mew", "mew", "mew");
	objects.push_back(tmp2);
	tmp.setTextures("spearDif", "spearNorm", "spearSpec", "spearGlow");
	tmp.geometry = "spear";
	tmp.opacity = 0.9f;
	tmp.position = glm::vec3(4.0f, 0.0f, 4.0f);
	tmp.angularVel = glm::vec3(0.25f, 0.33f, 0.58f);
	objects.push_back(tmp);
	tmp.setTextures("spearDif", "spearNorm", "spearSpec", "gray");
	tmp.opacity = 0.5f;
	tmp.position = glm::vec3(4.0f, 0.0f, 0.0f);
	tmp.angularVel = glm::vec3(0.58f, 0.33f, 0.25f);
	objects.push_back(tmp);
}

void gManager::stepObjects()
{
	for (int i = 0; i < objects.size(); i++)
	{
		obJect object = objects.at(i);
		object.position += (object.velocity * timer.getDeltaTime());
		object.rotation += (object.angularVel * timer.getDeltaTime());
		objects.at(i) = object;
	}
}


