#pragma once


#ifndef WINDOW_H
#define WINDOW_H


class Window
{
private:
	int width, height;
	char title[64];

	bool isInitialized = false;

	struct GLFWwindow *winHandle = nullptr;

public:
	bool init(int a_width = 800, int a_height = 600, char *a_title = "Sassafras");
	bool step();
	bool term();
	float getTime();

};


#endif
