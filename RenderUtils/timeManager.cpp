#include "GLFW\glfw3.h"

#include "timeManager.h"



bool timer::init()
{
	curTime = prevTime = deltaTime = 0.0f;
	glfwSetTime(0);
	return true;
}

bool timer::step()
{
	prevTime = curTime;
	curTime = getActualTime();
	deltaTime = curTime - prevTime;
	return true;
}

bool timer::term()
{
	return true;
}

float timer::getDeltaTime() const
{
	return deltaTime;
}

float timer::getTime() const
{
	return curTime;
}

float timer::getActualTime() const
{
	return glfwGetTime();
}
