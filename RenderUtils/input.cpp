#include "input.h"


#include "GLFW\glfw3.h"
#include "window.h"
#include <cstring>



bool input::init(const Window & window)
{
	if (!window.isInitialized)
	{
		return false;
	}
	memset(keys, 0, 1024 * sizeof(key_state));
	memset(mouseKeys, 0, 8 * sizeof(key_state));
	winHandle = window.winHandle;
	return true;
}

bool input::step()
{
	
	for (int i = 0; i < 1024; i++)
	{
		int press = glfwGetKey(winHandle, i);

		if ((keys[i] == UP || keys[i] == RELEASE )&& press == GLFW_PRESS)
		{
			keys[i] = PRESS;
		}
		else if ((keys[i] == DOWN || keys[i] == PRESS) && press == GLFW_RELEASE)
		{
			keys[i] = RELEASE;
		}
		else if (keys[i] == PRESS)
		{
			keys[i] = DOWN;
		}
		else if (keys[i] == RELEASE)
		{
			keys[i] = UP;
		}
	}
	int w, h;
	glfwGetWindowSize(winHandle, &w, &h);

	double xpos, ypos;
	prevMousePos[0] = curMousePos[0];
	prevMousePos[1] = curMousePos[1];
	glfwGetCursorPos(winHandle, &xpos, &ypos);
	curMousePos[0] = (float)xpos;
	curMousePos[1] = (float)ypos;
	deltaMousePos[0] = (curMousePos[0] - prevMousePos[0]) / (float)w;
	deltaMousePos[1] = (curMousePos[1] - prevMousePos[1]) / (float)h;


	for (int i = 0; i < 8; i++)
	{
		int press = glfwGetMouseButton(winHandle, i);

		if ((mouseKeys[i] == UP || mouseKeys[i] == RELEASE) && press == GLFW_PRESS)
		{
			mouseKeys[i] = PRESS;
		}
		else if ((mouseKeys[i] == DOWN || mouseKeys[i] == PRESS) && press == GLFW_RELEASE)
		{
			mouseKeys[i] = RELEASE;
		}
		else if (mouseKeys[i] == PRESS)
		{
			mouseKeys[i] = DOWN;
		}
		else if (mouseKeys[i] == RELEASE)
		{
			mouseKeys[i] = UP;
		}
	}

	return true;
}

bool input::term()
{
	return true;
}

void input::setCursorPos(double xPos, double yPos)
{
	glfwSetCursorPos(winHandle, xPos, yPos);
}

input::key_state input::getKeyState(int key) const
{
	return keys[key];
}

input::key_state input::getMouseButtonState(int button) const
{
	return mouseKeys[button];
}

void input::getMousePos(float & xPos, float & yPos) const
{
	xPos = curMousePos[0];
	yPos = curMousePos[1];
}

void input::getDeltaMouse(float & xPos, float & yPos) const
{
	xPos = deltaMousePos[0];
	yPos = deltaMousePos[1];
}

void input::hideCursor() const
{
	glfwSetInputMode(winHandle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void input::showCursor() const
{
	glfwSetInputMode(winHandle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}
