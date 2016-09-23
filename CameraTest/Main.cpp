

#include "window.h"
#include "gallery.h"
#include "timeManager.h"
#include "input.h"
#include "camera.h"
#include "procgen.h"

#include "crenderutils.h"

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

	//gallery.generatePlane("meow", 64, 64);

	//Geometry purple = genGrid(256, 75);

	unsigned char pixels[] ={125,125,0};
	Texture tex2 = makeTexture(1, 1, 0x1907, pixels);
	Texture tex = loadTexture("../res/textures/meow.jpg");
	Texture tex3 = loadTexture("../res/textures/MewMap.jpg");
	//Texture tex4 = genNoise(256, 1);

	gallery.loadShader("simple", "../res/shaders/simple.vs", "../res/shaders/simple.fs");
	gallery.loadShader("camera", "../res/shaders/camera.vs", "../res/shaders/camera.fs");
	gallery.loadShader("texture", "../res/shaders/texture.vs", "../res/shaders/texture.fs");
	gallery.loadShader("texture2", "../res/shaders/textureAlt.vs", "../res/shaders/textureAlt.fs");
	gallery.loadShader("gPass", "../res/shaders/gPass.vs", "../res/shaders/gPass.fs");
	gallery.loadShader("lPass", "../res/shaders/lPass.vs", "../res/shaders/lPass.fs", false, true);
	gallery.loadShader("post","../res/shaders/post.vs", "../res/shaders/post.fs");
	gallery.loadShader("nBlur", "../res/shaders/nBlur.vs", "../res/shaders/nBlur.fs", false);

	gallery.loadObjectOBJ("cube", "../res/models/cube.obj");
	gallery.loadObjectOBJ("sphere", "../res/models/sphere.obj");
	gallery.loadObjectOBJ("spear", "../res/models/soulspear.obj");
	//gallery.loadObjectOBJ("bunny", "../res/models/Bunny.obj");

	float ident[16] = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };

	glm::mat4 proj, view, model;


	proj = glm::perspective(45.0f, 1.0f, 0.10f, 20.0f);

	view = glm::lookAt(glm::vec3(5.0f, 5.0f , 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,1.0f, 0.0f));
	//model = glm::translate(glm::vec3(0.0f,0.0f,0.0f));
	cam.jumpTo(glm::vec3(5.0f, 5.0f, 5.0f));
	cam.lookAt(glm::vec3(0.0f, 0.0f, 0.0f));

	float curTime = 0.0f;

	float moveX = -3.0f, moveY = -3.0f, moveZ = -3.0f;


	glm::mat4 mod;
	gallery.loadShader("lighting", "../res/shaders/lighting.vs", "../res/shaders/lighting.fs");

	gallery.loadTexture("spearDif", "../res/textures/soulspear_diffuse.tga");
	gallery.loadTexture("spearNorm", "../res/textures/soulspear_normal.tga");
	gallery.loadTexture("spearSpec", "../res/textures/soulspear_specular.tga");

	Texture tray[] = {gallery.getTexture("spearDif"),gallery.getTexture("spearNorm"), gallery.getTexture("spearSpec")};
	//Texture atray[] = { tex4,tex4,tex4 };

	frameBuffer gFrame = makeFrameBuffer(1360, 768, 4);
	frameBuffer lFrame = makeFrameBuffer(1360, 768, 3);
	frameBuffer nFrame = makeFrameBuffer(1360, 768, 1);
	frameBuffer screen = { 0,1360,768,1 };



	gallery.makeGeometry("quee", quadVerts, 4, quadTris, 6);


	while (window.step())
	{
		clearFrameBuffer(gFrame);
		clearFrameBuffer(lFrame);
		clearFrameBuffer(nFrame);
		timer.step();
		input.step();
		
		view = cam.getView();
		proj = cam.getProjection();

		cam.update(input,timer);


		curTime = timer.getTime();


		mod = glm::rotate(curTime, glm::vec3(0.0f, 1.0f, 0.0f));
		tDraw(gallery.getShader("gPass"), gallery.getGeometry("spear"), gFrame, mod, view, proj, curTime, tray[0], tray[1], tray[2]);
		tDraw(gallery.getShader("gPass"), gallery.getGeometry("quee"), gFrame, glm::translate(glm::vec3(-2,0,-2)) * glm::rotate(45.0f, glm::vec3(0.0f,1.0f,0.0f)) * glm::scale(glm::vec3(2.0f,2.0f,1.0f)), view, proj, curTime, tex, tex, tex);
		tDraw(gallery.getShader("gPass"), gallery.getGeometry("sphere"), gFrame, mod, view, proj, curTime, tex, tex, tex);
		//draw(gallery.getShader("lighting"), gallery.getGeometry("spear"), frame, glm::value_ptr( glm::translate(glm::vec3(4.0f, 0.0f,0.0f)) * mod), glm::value_ptr(view), glm::value_ptr(proj), tray, 3, curTime);
		
		tDraw(gallery.getShader("nBlur"), gallery.getGeometry("quee"), nFrame, gFrame.colors[1], 3);

		tDraw(gallery.getShader("lPass"), gallery.getGeometry("quee"), lFrame, mod, view, proj, curTime, gFrame.colors[0], nFrame.colors[0], gFrame.colors[2], gFrame.colors[3], gFrame.depth, glm::normalize(glm::vec4(-1.0f, -1.0f, -1.0f, 0.0f)), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		tDraw(gallery.getShader("lPass"), gallery.getGeometry("quee"), lFrame, mod, view, proj, curTime, gFrame.colors[0], nFrame.colors[0], gFrame.colors[2], gFrame.colors[3], gFrame.depth, glm::normalize(glm::vec4(-1.0f, -1.0f, 0.0f, 0.0f)), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
		tDraw(gallery.getShader("lPass"), gallery.getGeometry("quee"), lFrame, mod, view, proj, curTime, gFrame.colors[0], nFrame.colors[0], gFrame.colors[2], gFrame.colors[3], gFrame.depth, glm::normalize(glm::vec4(0.0f, -1.0f, -1.0f, 0.0f)), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));


		tDraw(gallery.getShader("post"), gallery.getGeometry("quee"), screen, glm::scale(glm::vec3(0.5,0.5,1.0)), glm::mat4(), glm::mat4(), curTime, gFrame.colors[0], gFrame.colors[1], gFrame.colors[2]);

		for (int i = 0; i < 4; ++i)
		{
			glm::mat4 modr = glm::translate(glm::vec3(-0.75f + 0.5f * i, 0.5f, 0.0f)) * glm::scale(glm::vec3(0.25f, 0.5f, 1.0f));
			tDraw(gallery.getShader("post"), gallery.getGeometry("quee"), screen, modr, glm::mat4(), glm::mat4(), curTime, gFrame.colors[i], gFrame.colors[i], gFrame.colors[i]);


			tDraw(gallery.getShader("post"), gallery.getGeometry("quee"), screen, glm::translate(glm::vec3(0.0f, -1.0f, 0.0f)) * modr, glm::mat4(), glm::mat4(), curTime, lFrame.colors[i % 3], lFrame.colors[(i + 1) % 3], lFrame.colors[(i + 2)% 3]);
		}

		//draw(gallery.getShader("lighting"), gallery.getGeometry("bunny"), glm::value_ptr(mod * glm::translate(glm::vec3(20.0f,5.0f,0.0f))), glm::value_ptr(view), glm::value_ptr(proj), tray, 3, curTime);

		model = glm::rotate(curTime, glm::vec3(1.0f - fmod(curTime,1.0f), fmod(curTime,1.0f), fmod(curTime,1.0f)/0.5f));

		//draw(gallery.getShader("texture"), gallery.getGeometry("cube"), tex, glm::value_ptr(glm::rotate(curTime, glm::vec3(0, -fmod(curTime, 1.0f), 0)) * model), glm::value_ptr(view), glm::value_ptr(proj),curTime);
		//draw(gallery.getShader("texture"), gallery.getGeometry("sphere"),tex,  glm::value_ptr(glm::translate(glm::vec3(1.0f, 1.0f, 1.0f)) * model * glm::translate(glm::vec3(1.0f, 1.0f, 1.0f)) ), glm::value_ptr(view), glm::value_ptr(proj),curTime);
		//draw(gallery.getShader("texture"), gallery.getGeometry("sphere"), tex, glm::value_ptr(model * glm::translate(glm::vec3(1.0f, 0.0f, -1.0f))), glm::value_ptr(view), glm::value_ptr(proj), curTime);


		glm::mat4 mod2;
		mod2 = glm::scale(glm::vec3(0.5f,1.0f,0.5f)) * glm::translate(glm::vec3(-32.0f, -5.0f, -32.0f));

		//draw(gallery.getShader("texture2"), gallery.getGeometry("meow"), tex3, glm::value_ptr(mod2), glm::value_ptr(view), glm::value_ptr(proj), curTime);
		//draw(gallery.getShader("texture2"), purple, tex4, glm::value_ptr(mod2), glm::value_ptr(view), glm::value_ptr(proj), curTime);

		//draw(gallery.getShader("texture2"), gallery.getGeometry("cube"), tex, glm::value_ptr(mod), glm::value_ptr(view), glm::value_ptr(proj));

		//draw(gallery.getShader("texture"), gallery.getGeometry("cube"), tex, glm::value_ptr(glm::rotate(curTime, glm::vec3(0.0f, fmod(curTime, 1.0f), 0.0f)) * model * glm::translate(glm::vec3(3.0f, 1.0f, 0.0f))), glm::value_ptr(view), glm::value_ptr(proj), curTime);
		/*float test = fabs(fmod(curTime / 6.0f, 6.0f));
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
		draw(gallery.getShader("texture"), gallery.getGeometry("cube"),tex, glm::value_ptr(modelo), glm::value_ptr(view), glm::value_ptr(proj),curTime);*/
	}

	freeFrameBuffer(gFrame);


	freeTexture(tex);
	freeTexture(tex2);
	freeTexture(tex3);
//	freeTexture(tex4);

	input.term();
	timer.term();
	gallery.term();
	window.term();

	return;
}
