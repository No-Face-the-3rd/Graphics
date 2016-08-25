#pragma once


#ifndef WINDOW_H
#define WINDOW_H


class Window
{
private:
	int width, height;
	char title[64];

	bool isInitialized = false;

	class GLFWwindow *winHandle = nullptr;

public:
	bool init(int a_width, int a_height,char *a_title);
	bool step();
	bool term();

};


#endif
